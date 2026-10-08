#include "Solver/Algorithm/GoemansWilliamsonSolver.hpp"
#include "Model/CutResult.hpp"

namespace MaxCut
{
GoemansWilliamsonSolver::GoemansWilliamsonSolver(unsigned seed)
{
    m_rng.seed(seed);
}
CutResult GoemansWilliamsonSolver::Solve(const Graph &graph)
{
    (void)graph;
    std::vector<int> vectorA;
    std::vector<int> vectorB;

    CutResult cut(vectorA, vectorB, 0);
    return cut;
}
} // namespace MaxCut
