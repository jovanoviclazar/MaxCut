#pragma once

#include "Model/CutResult.hpp"
#include "Model/Graph.hpp"
#include "Solver/IMaxCutSolver.hpp"
#include <random>

namespace MaxCut
{
class GoemansWilliamsonSolver : public IMaxCutSolver
{

  private:
    std::mt19937 m_rng;

  public:
    GoemansWilliamsonSolver(unsigned seed);
    CutResult Solve(const Graph &graph) override;
};
} // namespace MaxCut
