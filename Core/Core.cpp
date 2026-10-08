#include "Core/Core.hpp"
#include "IO/GraphParser.hpp"
#include "IO/Output.hpp"
#include "Model/CutResult.hpp"
#include "Model/Graph.hpp"
#include "Solver/IMaxCutSolver.hpp"
#include "Solver/SolverFactory.hpp"
#include <iostream>
#include <memory>
#include <utility>

namespace MaxCut
{
Core::Core(Configuration config) : m_config(std::move(config))
{
}

int Core::Run() const
{
    const Graph graph = GraphParser::Parse(m_config.inputPath);

    const std::unique_ptr<IMaxCutSolver> solver = SolverFactory::Create(m_config.algorithm, m_config.seed);

    const CutResult result = solver->Solve(graph);

    if (m_config.outputPath)
    {
        Output::WriteToFile(*m_config.outputPath, result);
    }
    else
    {
        std::cout << result;
    }

    return 0;
}
} // namespace MaxCut
