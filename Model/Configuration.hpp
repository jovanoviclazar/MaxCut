#pragma once

#include <optional>
#include <string>

namespace MaxCut
{
struct Configuration
{
    std::string inputPath;
    std::optional<std::string> outputPath;
    std::string algorithm = "random";
    unsigned seed = 0;
};
} // namespace MaxCut
