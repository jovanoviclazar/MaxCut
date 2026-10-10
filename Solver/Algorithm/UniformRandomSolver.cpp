#include "Solver/Algorithm/UniformRandomSolver.hpp"

namespace MaxCut
{
UniformRandomSolver::UniformRandomSolver(unsigned seed)
{
    m_rng.seed(seed);
}
CutResult UniformRandomSolver::Solve(const Graph &graph)
{
    (void)graph;
    std::vector<size_t> vectorA;
    std::vector<size_t> vectorB;

    CutResult cut(vectorA, vectorB, 0);
    return cut;
}
} // namespace MaxCut
