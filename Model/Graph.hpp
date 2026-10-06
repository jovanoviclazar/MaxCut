#pragma once

#include <vector>

namespace MaxCut
{
class Graph
{
  private:
    int NumberOfEdges{};
    int NumberOfVertices{};
    std::vector<std::vector<double>> Connections;

  public:
    Graph() = default;
    Graph(int numberOfEdges, int numberOfVertices, std::vector<std::vector<double>> &connections);
};
} // namespace MaxCut
