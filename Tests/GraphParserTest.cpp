#include "Model/Graph.hpp"
#include <catch2/catch_test_macros.hpp>
#include <vector>

namespace MaxCut
{
namespace
{

std::vector<std::vector<double>> TriangleMatrix()
{
    return {
        {0.0, 1.0, 2.0},
        {1.0, 0.0, 3.0},
        {2.0, 3.0, 0.0},
    };
}

} // namespace

TEST_CASE("Graph stores vertex and edge counts", "[graph]")
{
    auto connections = TriangleMatrix();
    const Graph graph(3, 3, connections);

    REQUIRE(graph.NumberOfEdges() == 3);
    REQUIRE(graph.NumberOfVertices() == 3);
}

TEST_CASE("Graph does not swap edges and vertices", "[graph]")
{
    std::vector<std::vector<double>> connections(5, std::vector<double>(5, 0.0));
    const Graph graph(2, 5, connections);

    REQUIRE(graph.NumberOfEdges() == 2);
    REQUIRE(graph.NumberOfVertices() == 5);
}

TEST_CASE("Graph stores connections", "[graph]")
{
    auto connections = TriangleMatrix();
    const Graph graph(3, 3, connections);

    REQUIRE(graph.Connections() == TriangleMatrix());
}

TEST_CASE("Graph connections matrix is symmetric", "[graph]")
{
    auto connections = TriangleMatrix();
    const Graph graph(3, 3, connections);

    const auto matrix = graph.Connections();
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < matrix.size(); ++j)
        {
            REQUIRE(matrix[i][j] == matrix[j][i]);
        }
    }
}

TEST_CASE("Empty graph", "[graph]")
{
    std::vector<std::vector<double>> connections;
    const Graph graph(0, 0, connections);

    REQUIRE(graph.NumberOfEdges() == 0);
    REQUIRE(graph.NumberOfVertices() == 0);
    REQUIRE(graph.Connections().empty());
}

TEST_CASE("Graph constructor moves from the caller's matrix", "[graph]")
{
    auto connections = TriangleMatrix();
    const Graph graph(3, 3, connections);

    REQUIRE(connections.empty());
}

} // namespace MaxCut
