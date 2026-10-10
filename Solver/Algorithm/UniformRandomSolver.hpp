#pragma once

#include "Model/CutResult.hpp"
#include "Model/Graph.hpp"
#include "Solver/IMaxCutSolver.hpp"
#include <random>

namespace MaxCut
{
class UniformRandomSolver : public IMaxCutSolver
{
  private:
    std::mt19937 m_rng;

  public:
    UniformRandomSolver(unsigned seed);
    CutResult Solve(const Graph &graph) override;
};
} // namespace MaxCut
