#include "Solver/Algorithm/BruteForceSolver.hpp"

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

void bruteSolve(size_t i, std::vector<size_t> &vectorA, std::vector<size_t> &vectorB, double &cutCost,
                std::vector<size_t> &tmpVectorA, std::vector<size_t> &tmpVectorB, const Graph &graph)
{
    if (i == graph.NumberOfVertices())
    {
        const double tmpCutCost = computeCost(tmpVectorA, tmpVectorB, graph);
        if (cutCost < tmpCutCost)
        {
            cutCost = tmpCutCost;
            vectorA = std::vector<size_t>(tmpVectorA);
            vectorB = std::vector<size_t>(tmpVectorB);
        }
        return;
    }
    tmpVectorA.push_back(i);
    bruteSolve(i + 1, vectorA, vectorB, cutCost, tmpVectorA, tmpVectorB, graph);
    tmpVectorA.pop_back();
    tmpVectorB.push_back(i);
    bruteSolve(i + 1, vectorA, vectorB, cutCost, tmpVectorA, tmpVectorB, graph);
    tmpVectorB.pop_back();
}
} // namespace

CutResult BruteForceSolver::Solve(const Graph &graph)
{
    std::vector<size_t> vectorA;
    std::vector<size_t> vectorB;
    double cutCost = 0.0;

    std::vector<size_t> tmpVectorA({});
    std::vector<size_t> tmpVectorB({});

    bruteSolve(0, vectorA, vectorB, cutCost, tmpVectorA, tmpVectorB, graph);

    CutResult cut(vectorA, vectorB, cutCost);
    return cut;
}
} // namespace MaxCut
