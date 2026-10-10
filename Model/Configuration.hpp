#pragma once

#include <optional>
#include <string>

namespace MaxCut
{
struct Configuration
{
    std::string inputPath = "Dummy.txt";
    std::optional<std::string> outputPath;
    std::string algorithm = "brute";
    unsigned seed = 0;
};
} // namespace MaxCut
