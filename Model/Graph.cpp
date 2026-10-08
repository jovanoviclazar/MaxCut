#include "Model/Graph.hpp"
#include <utility>

namespace MaxCut
{
Graph::Graph(int numberOfEdges, int numberOfVertices, std::vector<std::vector<double>> &connections)
    : m_numberOfEdges(numberOfEdges), m_numberOfVertices(numberOfVertices), m_connections(std::move(connections))
{
}
} // namespace MaxCut
