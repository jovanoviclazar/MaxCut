#include "Solver/Algorithm/GoemansWilliamsonSolver.hpp"
#include "Model/CutResult.hpp"
#include "Model/Graph.hpp"
#include <clarabel.hpp>
#include <numbers>
#include <random>
#include <vector>

namespace MaxCut
{
GoemansWilliamsonSolver::GoemansWilliamsonSolver(unsigned seed) : m_rng(seed)
{
}
namespace
{

// Clarabel solves:   minimize    (1/2) x'Px + q'x
//                    subject to  Ax + s = b,  s in K
//
// We want  maximize (1/4) <L, X>  subject to  X_ii = 1  and  X positive semidefinite,
// where L is the weighted Laplacian. This is the same as minimizing -(1/4) <L, X>.
// The unknown x is the upper triangle of X, stored column by column.
//
//   P  quadraticCost             all zeros, the objective is linear
//   q  objectiveCoefficients     -L_ii / 4 on the diagonal, -L_ij / 2 off it
//   A  constraintMatrix          rows 0..n-1:   X_ii = 1                (zero cone)
//                                rows n..:      -scale * x_k            (PSD cone)
//   b  constraintRightSide   1 for the first n rows, 0 for the rest
//   K  cones                     ZeroConeT(n), PSDTriangleConeT(n)

Eigen::MatrixXd SolveSdpRelaxation(const Graph &graph)
{
    const long vertexCount = static_cast<long>(graph.NumberOfVertices());

    Eigen::MatrixXd weightMatrix(vertexCount, vertexCount);

    for (long i = 0; i < vertexCount; i++)
    {
        for (long j = 0; j < vertexCount; j++)
        {
            weightMatrix(i, j) = graph.Connections()[i][j];
        }
    }

    const Eigen::VectorXd weightedDegrees = weightMatrix.rowwise().sum();
    const Eigen::MatrixXd laplacian = weightedDegrees.asDiagonal().toDenseMatrix() - weightMatrix;

    const long triangleSize = vertexCount * (vertexCount + 1) / 2;
    Eigen::VectorXd objectiveCoefficients(triangleSize);
    Eigen::VectorXd constraintRightSide = Eigen::VectorXd::Zero(vertexCount + triangleSize);
    std::vector<Eigen::Triplet<double>> constraintTriplets;

    for (long i = 0; i < vertexCount; i++)
    {
        for (long j = 0; j <= i; j++)
        {
            const long triangleIndex = (i * (i + 1) / 2) + j;
            const bool isDiagonal = (j == i);

            objectiveCoefficients(triangleIndex) = isDiagonal ? -laplacian(j, j) / 4.0 : -laplacian(j, i) / 2.0;
            constraintTriplets.emplace_back(static_cast<int>(vertexCount + triangleIndex),
                                            static_cast<int>(triangleIndex), isDiagonal ? -1.0 : -std::numbers::sqrt2);

            if (isDiagonal)
            {
                constraintTriplets.emplace_back(static_cast<int>(j), static_cast<int>(triangleIndex), 1.0);
                constraintRightSide(j) = 1.0;
            }
        }
    }

    Eigen::SparseMatrix<double> constraintMatrix(vertexCount + triangleSize, triangleSize);
    constraintMatrix.setFromTriplets(constraintTriplets.begin(), constraintTriplets.end());
    constraintMatrix.makeCompressed();

    Eigen::SparseMatrix<double> quadraticCost(triangleSize, triangleSize);
    quadraticCost.makeCompressed();

    const std::vector<clarabel::SupportedConeT<double>> cones{
        clarabel::ZeroConeT<double>(vertexCount),
        clarabel::PSDTriangleConeT<double>(vertexCount),
    };

    const clarabel::DefaultSettings<double> settings =
        clarabel::DefaultSettingsBuilder<double>::default_settings().verbose(false).max_iter(100).build();

    clarabel::DefaultSolver<double> sdpSolver(quadraticCost, objectiveCoefficients, constraintMatrix,
                                              constraintRightSide, cones, settings);
    sdpSolver.solve();
    const clarabel::DefaultSolution<double> sdpSolution = sdpSolver.solution();

    if (sdpSolution.status != clarabel::SolverStatus::Solved)
    {
        throw std::runtime_error("Clarabel did not solve the Goemans-Williamson relaxation.");
    }

    Eigen::MatrixXd gramMatrix(vertexCount, vertexCount);
    for (long column = 0; column < vertexCount; column++)
    {
        for (long row = 0; row <= column; row++)
        {
            gramMatrix(row, column) = sdpSolution.x[(column * (column + 1) / 2) + row];
            gramMatrix(column, row) = gramMatrix(row, column);
        }
    }
    return gramMatrix;
}

// We want to factor the Gram matrix X into vertex vectors V such that X = V'V.
// Using spectral decomposition X = Q * Lambda * Q', we split it into (Q * sqrt(Lambda)) * (Q * sqrt(Lambda))'.

Eigen::MatrixXd ComputeVertexVectors(const Eigen::MatrixXd &gramMatrix)
{
    const Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigenSolver(gramMatrix);
    if (eigenSolver.info() != Eigen::Success)
    {
        throw std::runtime_error("Eigen decomposition failed during Goemans-Williamson rounding.");
    }

    const Eigen::VectorXd sqrtEigenvalues = eigenSolver.eigenvalues().cwiseMax(0.0).cwiseSqrt();
    Eigen::MatrixXd vertexVectors = eigenSolver.eigenvectors() * sqrtEigenvalues.asDiagonal();
    for (long i = 0; i < vertexVectors.rows(); i++)
    {
        vertexVectors.row(i).normalize();
    }
    return vertexVectors;
}

CutResult RoundWithRandomHyperplane(const Graph &graph, const Eigen::MatrixXd &vertexVectors, std::mt19937 &rng)
{
    const long vertexCount = static_cast<long>(vertexVectors.rows());

    std::normal_distribution<double> gaussian(0.0, 1.0);

    Eigen::VectorXd hyperplaneNormal(vertexVectors.cols());
    for (long i = 0; i < hyperplaneNormal.size(); i++)
    {
        hyperplaneNormal(i) = gaussian(rng);
    }

    std::vector<size_t> vectorA;
    std::vector<size_t> vectorB;
    double cutWeight = 0.0;

    for (long i = 0; i < vertexCount; i++)
    {
        const double projectionOnNormal = hyperplaneNormal.dot(vertexVectors.row(i));
        if (projectionOnNormal >= 0.0)
        {
            vectorA.push_back(static_cast<size_t>(i));
        }
        else
        {
            vectorB.push_back(static_cast<size_t>(i));
        }
    }

    const long vectorASize = static_cast<long>(vectorA.size());
    const long vectorBSize = static_cast<long>(vectorB.size());
    for (long i = 0; i < vectorASize; i++)
    {
        for (long j = 0; j < vectorBSize; j++)
        {
            cutWeight += graph.Connections()[vectorA[i]][vectorB[j]];
        }
    }

    return {vectorA, vectorB, cutWeight};
}
} // namespace

CutResult GoemansWilliamsonSolver::Solve(const Graph &graph)
{
    const Eigen::MatrixXd gramMatrix = SolveSdpRelaxation(graph);
    const Eigen::MatrixXd vertexVectors = ComputeVertexVectors(gramMatrix);
    return RoundWithRandomHyperplane(graph, vertexVectors, m_rng);
}
} // namespace MaxCut
