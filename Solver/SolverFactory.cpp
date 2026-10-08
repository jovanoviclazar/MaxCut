#include "Solver/SolverFactory.hpp"
#include "Solver/Algorithm/BasicRandomSolver.hpp"
#include "Solver/Algorithm/BruteForceSolver.hpp"
#include "Solver/Algorithm/GoemansWilliamsonSolver.hpp"
#include <functional>
#include <map>
#include <stdexcept>

namespace MaxCut
{
using Creator = std::function<std::unique_ptr<IMaxCutSolver>(unsigned)>;

const std::map<std::string, std::function<std::unique_ptr<IMaxCutSolver>(unsigned)>> &SolverFactory::Registry()
{
    static const std::map<std::string, std::function<std::unique_ptr<IMaxCutSolver>(unsigned)>> registry = {
        {"random", [](unsigned seed) { return std::make_unique<BasicRandomSolver>(seed); }},
        {"brute", [](unsigned) { return std::make_unique<BruteForceSolver>(); }},
        {"gw", [](unsigned seed) { return std::make_unique<GoemansWilliamsonSolver>(seed); }},
    };
    return registry;
}

std::unique_ptr<IMaxCutSolver> SolverFactory::Create(const std::string &name, unsigned seed)
{
    const auto &registry = Registry();
    const auto it = registry.find(name);
    if (it == registry.end())
    {
        throw std::runtime_error("Unknown algorithm: " + name);
    }
    return it->second(seed);
}

} // namespace MaxCut
