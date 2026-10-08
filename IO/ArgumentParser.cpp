#include "IO/ArgumentParser.hpp"
#include "Model/Configuration.hpp"
#include <string>
#include <vector>

namespace MaxCut
{

std::vector<std::string> ArgumentParser::ConvertArgs(int argc, char **argv)
{
    std::vector<std::string> returnValue;
    returnValue.reserve(argc);

    for (int i = 0; i < argc; i++)
    {
        returnValue.emplace_back(argv[i]);
    }

    return returnValue;
}

Configuration ArgumentParser::Parse(int argc, char **argv)
{
    const std::vector<std::string> args(ArgumentParser::ConvertArgs(argc, argv));
    Configuration config;

    return config;
}

} // namespace MaxCut
