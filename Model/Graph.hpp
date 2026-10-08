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
    int NumberOfEdges() const;
    int NumberOfVertices() const;
    std::vector<std::vector<double>> Connections() const;
};
} // namespace MaxCut
