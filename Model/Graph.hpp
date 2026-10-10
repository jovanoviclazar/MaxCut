#pragma once

#include <vector>

namespace MaxCut
{
class Graph
{
  private:
    size_t m_numberOfEdges{};
    size_t m_numberOfVertices{};
    std::vector<std::vector<double>> m_connections;

  public:
    Graph() = default;
    Graph(size_t numberOfEdges, size_t numberOfVertices, std::vector<std::vector<double>> &connections);
    size_t NumberOfEdges() const;
    size_t NumberOfVertices() const;
    const std::vector<std::vector<double>> &Connections() const;
};
} // namespace MaxCut
