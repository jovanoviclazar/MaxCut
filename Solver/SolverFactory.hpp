#pragma once

#include "Solver/IMaxCutSolver.hpp"
#include <functional>
#include <map>
#include <memory>
#include <string>

namespace MaxCut
{

class SolverFactory
{
  private:
    using Creator = std::function<std::unique_ptr<IMaxCutSolver>(unsigned)>;

    static const std::map<std::string, Creator> &Registry();

  public:
    SolverFactory() = delete;

    static std::unique_ptr<IMaxCutSolver> Create(const std::string &name, unsigned seed);
};

} // namespace MaxCut
