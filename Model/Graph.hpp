#pragma once

#include <string>
#include <utility>
#include <vector>

namespace MaxCut
{
class Graph
{
  private:
    int NumberOfVertices = 0;
    int NumberOfEdges = 0;
    std::vector<std::vector<std::pair<int, double>>> Connections;

  public:
    Graph(std::string &FileName);
    Graph() = default;
};
} // namespace MaxCut
