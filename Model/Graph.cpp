#include "Model/Graph.hpp"
#include <filesystem>
#include <fstream>
#include <string>

namespace MaxCut
{
Graph::Graph(std::string &FileName)
{
    const std::filesystem::path path = std::filesystem::path("Instances") / FileName;

    std::ifstream file(path);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file: " + path.string());
    }

    if (!(file >> NumberOfVertices >> NumberOfEdges))
    {
        throw std::runtime_error("Invalid header in: " + path.string());
    }

    Connections.resize(NumberOfVertices);

    for (int i = 0; i < NumberOfEdges; i++)
    {
        int u;
        int v;
        double w;
        if (!(file >> u >> v >> w))
        {
            throw std::runtime_error("Invalid edge on line: " + std::to_string(i + 2));
        }
        Connections[u].emplace_back(v, w);
        Connections[v].emplace_back(u, w);
    }
}
} // namespace MaxCut
