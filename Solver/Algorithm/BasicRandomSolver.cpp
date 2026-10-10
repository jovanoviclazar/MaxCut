#include "Solver/Algorithm/BasicRandomSolver.hpp"

namespace MaxCut
{
BasicRandomSolver::BasicRandomSolver(unsigned seed)
{
    m_rng.seed(seed);
}
CutResult BasicRandomSolver::Solve(const Graph &graph)
{
    (void)graph;
    std::vector<size_t> vectorA;
    std::vector<size_t> vectorB;

    CutResult cut(vectorA, vectorB, 0);
    return cut;
}
} // namespace MaxCut
