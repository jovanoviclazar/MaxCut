#include "Solver/Algorithm/UniformRandomSolver.hpp"
#include <cstdlib>

namespace MaxCut
{
namespace
{
double computeCost(std::vector<size_t> &tmpVectorA, std::vector<size_t> &tmpVectorB, const Graph &graph)
{
    double returnCutCost = 0.0;
    for (const size_t x : tmpVectorA)
    {
        for (const size_t y : tmpVectorB)
        {
            returnCutCost += graph.Connections()[x][y];
        }
    }
    return returnCutCost;
}
} // namespace
UniformRandomSolver::UniformRandomSolver(unsigned seed)
{
    m_rng.seed(seed);
}
CutResult UniformRandomSolver::Solve(const Graph &graph)
{
    std::vector<size_t> vectorA;
    std::vector<size_t> vectorB;

    std::uniform_int_distribution<int> dist(0, 1);

    for (size_t i = 0; i < graph.NumberOfVertices(); i++)
    {
        const int randomNumber = dist(m_rng);
        if (randomNumber == 0)
        {
            vectorA.push_back(i);
        }
        else
        {
            vectorB.push_back(i);
        }
    }

    const double cutCost = computeCost(vectorA, vectorB, graph);

    CutResult cut(vectorA, vectorB, cutCost);
    return cut;
}
} // namespace MaxCut
