#include "Model/Graph.hpp"
#include <utility>

namespace MaxCut
{
Graph::Graph(int numberOfEdges, int numberOfVertices, std::vector<std::vector<double>> &connections)
    : NumberOfEdges(numberOfEdges), NumberOfVertices(numberOfVertices), Connections(std::move(connections))
{
}
} // namespace MaxCut
