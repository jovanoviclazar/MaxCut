// Tests/GreedySolverTest.cpp
#include "Solver/Algorithm/GreedySolver.hpp"
#include "Model/Graph.hpp"
#include <algorithm>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include <tuple>
#include <vector>

namespace MaxCut::Testing
{
// NOLINTBEGIN(cppcoreguidelines-avoid-do-while, bugprone-chained-comparison, misc-use-anonymous-namespace,
// bugprone-throwing-static-initialization, cert-err58-cpp, readability-function-cognitive-complexity)
namespace
{

using Edge = std::tuple<int, int, double>;

Graph MakeGraph(size_t vertices, const std::vector<Edge> &edges)
{
    std::vector<std::vector<double>> connections(vertices, std::vector<double>(vertices, 0.0));
    for (const auto &[u, v, w] : edges)
    {
        connections[u][v] = w;
        connections[v][u] = w;
    }
    return {static_cast<size_t>(edges.size()), vertices, connections};
}

double CutWeightOf(size_t vertices, const std::vector<size_t> &a, const std::vector<size_t> &b,
                   const std::vector<Edge> &edges)
{
    std::vector<int> side(vertices, -1);
    for (size_t v : a)
    {
        side[v] = 0;
    }
    for (size_t v : b)
    {
        side[v] = 1;
    }

    double weight = 0.0;
    for (const auto &[u, v, w] : edges)
    {
        if (side[u] != side[v])
        {
            weight += w;
        }
    }
    return weight;
}

void CheckResultIsConsistent(size_t vertices, const std::vector<Edge> &edges)
{
    const Graph graph = MakeGraph(vertices, edges);
    GreedySolver solver;
    const CutResult result = solver.Solve(graph);

    const auto &a = result.VectorA();
    const auto &b = result.VectorB();

    std::vector<size_t> all(a.begin(), a.end());
    all.insert(all.end(), b.begin(), b.end());
    std::sort(all.begin(), all.end());
    std::vector<size_t> expected(vertices);
    std::iota(expected.begin(), expected.end(), size_t{0});
    CHECK(all == expected);

    CHECK(result.CutCost() == Catch::Approx(CutWeightOf(vertices, a, b, edges)));
}

} // namespace

TEST_CASE("GreedySolver returns a valid partition with a consistent cost", "[greedy]")
{
    SECTION("Single edge")
    {
        CheckResultIsConsistent(2, {{0, 1, 5.0}});
    }

    SECTION("Path of three vertices")
    {
        CheckResultIsConsistent(3, {{0, 1, 1.0}, {1, 2, 1.0}});
    }

    SECTION("Weighted triangle")
    {
        CheckResultIsConsistent(3, {{0, 1, 1.0}, {1, 2, 3.0}, {0, 2, 2.0}});
    }

    SECTION("Even cycle")
    {
        CheckResultIsConsistent(4, {{0, 1, 1.0}, {1, 2, 1.0}, {2, 3, 1.0}, {3, 0, 1.0}});
    }

    SECTION("Complete graph K4")
    {
        CheckResultIsConsistent(4, {{0, 1, 1.0}, {0, 2, 1.0}, {0, 3, 1.0}, {1, 2, 1.0}, {1, 3, 1.0}, {2, 3, 1.0}});
    }

    SECTION("Disconnected components")
    {
        CheckResultIsConsistent(4, {{0, 1, 2.0}, {2, 3, 3.0}});
    }

    SECTION("No edges")
    {
        CheckResultIsConsistent(3, {});
    }
}

TEST_CASE("GreedySolver edge cases", "[greedy]")
{
    SECTION("Single vertex")
    {
        const Graph graph = MakeGraph(1, {});
        GreedySolver solver;
        const CutResult result = solver.Solve(graph);

        CHECK(result.VectorA() == std::vector<size_t>{0});
        CHECK(result.VectorB().empty());
        CHECK(result.CutCost() == Catch::Approx(0.0));
    }
}
// NOLINTEND(cppcoreguidelines-avoid-do-while, bugprone-chained-comparison, misc-use-anonymous-namespace,
// bugprone-throwing-static-initialization, cert-err58-cpp, readability-function-cognitive-complexity)
} // namespace MaxCut::Testing
