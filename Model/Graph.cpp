#include "Model/Graph.hpp"
#include <utility>

namespace MaxCut
{
Graph::Graph(size_t numberOfEdges, size_t numberOfVertices, std::vector<std::vector<double>> &connections)
    : m_numberOfEdges(numberOfEdges), m_numberOfVertices(numberOfVertices), m_connections(std::move(connections))
{
}
size_t Graph::NumberOfEdges() const
{
    return m_numberOfEdges;
}
size_t Graph::NumberOfVertices() const
{
    return m_numberOfVertices;
}
const std::vector<std::vector<double>> &Graph::Connections() const
{
    return m_connections;
}
} // namespace MaxCut
