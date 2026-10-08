#include "IO/GraphParser.hpp"
#include "Model/Graph.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace MaxCut
{
Graph GraphParser::Parse(const std::string &fileName)
{
    int numberOfVertices;
    int numberOfEdges;
    std::vector<std::vector<double>> connections;

    const std::filesystem::path path = std::filesystem::path("Instances") / fileName;

    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + path.string());
    }

    if (!(file >> numberOfVertices >> numberOfEdges))
    {
        throw std::runtime_error("Invalid header in: " + path.string());
    }

    connections.assign(numberOfVertices, std::vector<double>(numberOfVertices, 0.0));

    for (int i = 0; i < numberOfEdges; i++)
    {
        int u;
        int v;
        double w;
        if (!(file >> u >> v >> w))
        {
            throw std::runtime_error("Invalid edge on line: " + std::to_string(i + 2));
        }
        connections[u][v] = connections[v][u] = w;
    }
    Graph graph(numberOfEdges, numberOfVertices, connections);

    return graph;
}

} // namespace MaxCut
