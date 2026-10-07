#pragma once

#include "Model/CutResult.hpp"
#include "Model/Graph.hpp"
namespace MaxCut
{
class IMaxCutSolver
{
  public:
    virtual ~IMaxCutSolver() = default;

    IMaxCutSolver() = default;
    IMaxCutSolver(const IMaxCutSolver &) = delete;
    IMaxCutSolver &operator=(const IMaxCutSolver &) = delete;
    IMaxCutSolver(IMaxCutSolver &&) = delete;
    IMaxCutSolver &operator=(IMaxCutSolver &&) = delete;

    virtual CutResult Solve(const Graph &graph) = 0;
    virtual CutResult Solve(Graph &graph);
};
} // namespace MaxCut
