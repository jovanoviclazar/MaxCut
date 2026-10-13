#pragma once

#include "Model/CutResult.hpp"
#include "Model/Graph.hpp"
#include "Solver/IMaxCutSolver.hpp"

namespace MaxCut
{
class GreedySolver : public IMaxCutSolver
{
  public:
    CutResult Solve(const Graph &graph) override;
};
} // namespace MaxCut
