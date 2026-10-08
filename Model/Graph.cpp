#include "Model/Graph.hpp"
#include <utility>

namespace MaxCut
{
Graph::Graph(int numberOfEdges, int numberOfVertices, std::vector<std::vector<double>> &connections)
    : m_numberOfEdges(numberOfEdges), m_numberOfVertices(numberOfVertices), m_connections(std::move(connections))
{
}
int Graph::NumberOfEdges() const
{
    return m_numberOfEdges;
}
int Graph::NumberOfVertices() const
{
    return m_numberOfVertices;
}
std::vector<std::vector<double>> Graph::Connections() const
{
    return m_connections;
}
} // namespace MaxCut
