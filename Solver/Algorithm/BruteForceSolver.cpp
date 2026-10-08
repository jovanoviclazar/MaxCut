#include "Solver/Algorithm/BruteForceSolver.hpp"

namespace MaxCut
{
CutResult BruteForceSolver::Solve(const Graph &graph)
{
    (void)graph;
    std::vector<int> vectorA;
    std::vector<int> vectorB;

    CutResult cut(vectorA, vectorB, 0);
    return cut;
}
} // namespace MaxCut
