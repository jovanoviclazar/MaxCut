#include "IO/GraphParser.hpp"
#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

namespace MaxCut::Testing
{

namespace
{

class TempInstance
{
  public:
    TempInstance(std::string name, const std::string &content)
        : m_name(std::move(name)), m_path(std::filesystem::path("Instances") / m_name)
    {
        std::filesystem::create_directories("Instances");
        std::ofstream file(m_path);
        file << content;
    }

    TempInstance(const TempInstance &) = delete;
    TempInstance &operator=(const TempInstance &) = delete;
    TempInstance(TempInstance &&) = delete;
    TempInstance &operator=(TempInstance &&) = delete;

    ~TempInstance()
    {
        std::error_code ec;
        std::filesystem::remove(m_path, ec);
    }

    const std::string &Name() const
    {
        return m_name;
    }

  private:
    std::string m_name;
    std::filesystem::path m_path;
};

} // namespace
// NOLINTBEGIN(cppcoreguidelines-avoid-do-while, bugprone-chained-comparison, misc-use-anonymous-namespace,
// bugprone-throwing-static-initialization, cert-err58-cpp, readability-function-cognitive-complexity)
TEST_CASE("GraphParser parses a valid graph", "[graph-parser]")
{
    const TempInstance instance("valid_graph.txt", "3 2\n0 1 1.5\n1 2 2.0\n");

    const Graph graph = GraphParser::Parse(instance.Name());

    CHECK(graph.NumberOfVertices() == 3);
    CHECK(graph.NumberOfEdges() == 2);

    const auto connections = graph.Connections();
    REQUIRE(connections.size() == 3);
    CHECK(connections[0][1] == 1.5);
    CHECK(connections[1][2] == 2.0);
    CHECK(connections[0][2] == 0.0);
}

TEST_CASE("GraphParser produces a symmetric matrix", "[graph-parser]")
{
    const TempInstance instance("symmetric_graph.txt", "3 2\n0 1 1.5\n1 2 2.0\n");

    const Graph graph = GraphParser::Parse(instance.Name());
    const auto connections = graph.Connections();

    for (size_t i = 0; i < connections.size(); ++i)
    {
        for (size_t j = 0; j < connections.size(); ++j)
        {
            CHECK(connections[i][j] == connections[j][i]);
        }
    }
}

TEST_CASE("GraphParser parses an empty graph", "[graph-parser]")
{
    const TempInstance instance("empty_graph.txt", "0 0\n");

    const Graph graph = GraphParser::Parse(instance.Name());

    CHECK(graph.NumberOfVertices() == 0);
    CHECK(graph.NumberOfEdges() == 0);
    CHECK(graph.Connections().empty());
}

TEST_CASE("GraphParser error handling", "[graph-parser]")
{
    SECTION("Throws on missing file")
    {
        REQUIRE_THROWS_AS(GraphParser::Parse("does_not_exist.txt"), std::runtime_error);
    }

    SECTION("Throws on invalid header")
    {
        const TempInstance instance("bad_header.txt", "not a header\n");
        REQUIRE_THROWS_AS(GraphParser::Parse(instance.Name()), std::runtime_error);
    }

    SECTION("Throws on empty file")
    {
        const TempInstance instance("empty_file.txt", "");
        REQUIRE_THROWS_AS(GraphParser::Parse(instance.Name()), std::runtime_error);
    }

    SECTION("Throws when an edge line is incomplete")
    {
        const TempInstance instance("bad_edge.txt", "3 2\n0 1 1.0\n1 2\n");
        REQUIRE_THROWS_AS(GraphParser::Parse(instance.Name()), std::runtime_error);
    }

    SECTION("Throws when fewer edges are present than declared")
    {
        const TempInstance instance("missing_edge.txt", "3 2\n0 1 1.0\n");
        REQUIRE_THROWS_AS(GraphParser::Parse(instance.Name()), std::runtime_error);
    }
}
// NOLINTEND(cppcoreguidelines-avoid-do-while, bugprone-chained-comparison, misc-use-anonymous-namespace,
// bugprone-throwing-static-initialization, cert-err58-cpp, readability-function-cognitive-complexity)
} // namespace MaxCut::Testing
