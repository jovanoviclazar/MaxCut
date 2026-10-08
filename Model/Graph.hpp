#pragma once

#include <vector>

namespace MaxCut
{
class Graph
{
  private:
    int m_numberOfEdges{};
    int m_numberOfVertices{};
    std::vector<std::vector<double>> m_connections;

  public:
    Graph() = default;
    Graph(int numberOfEdges, int numberOfVertices, std::vector<std::vector<double>> &connections);
};
} // namespace MaxCut
