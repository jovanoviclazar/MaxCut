#pragma once

#include "Model/CutResult.hpp"
#include "Model/Graph.hpp"
#include "Solver/IMaxCutSolver.hpp"

namespace MaxCut
{
class BruteForceSolver : public IMaxCutSolver
{
  public:
    CutResult Solve(const Graph &graph) override;
};
} // namespace MaxCut
