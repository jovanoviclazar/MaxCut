#pragma once

#include "Model/Graph.hpp"
#include <string>

namespace MaxCut
{
class GraphParser
{
    static Graph Parse(const std::string &fileName);
};
}; // namespace MaxCut
