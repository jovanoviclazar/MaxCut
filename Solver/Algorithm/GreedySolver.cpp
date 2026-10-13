#include "Solver/Algorithm/GreedySolver.hpp"

namespace MaxCut
{
CutResult GreedySolver::Solve(const Graph &graph)
{
    std::vector<size_t> vectorA;
    std::vector<size_t> vectorB;
    double cutCost = 0.0;

    vectorA.push_back(0);

    for (size_t i = 1; i < graph.NumberOfVertices(); i++)
    {
        double cutCostA = 0.0;
        double cutCostB = 0.0;

        for (size_t x : vectorA)
        {
            cutCostA += graph.Connections()[i][x];
        }
        for (size_t x : vectorB)
        {
            cutCostB += graph.Connections()[i][x];
        }

        if (cutCostA < cutCostB)
        {
            vectorA.push_back(i);
            cutCost += cutCostB;
        }
        else
        {
            vectorB.push_back(i);
            cutCost += cutCostA;
        }
    }

    return {vectorA, vectorB, cutCost};
}
} // namespace MaxCut
