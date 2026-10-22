#include "Solver/Algorithm/UniformRandomSolver.hpp"
#include "Model/Graph.hpp"
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <tuple>
#include <vector>

namespace MaxCut::Testing
{

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

} // namespace

// NOLINTBEGIN(cppcoreguidelines-avoid-do-while, bugprone-chained-comparison, misc-use-anonymous-namespace,
// bugprone-throwing-static-initialization, cert-err58-cpp, readability-function-cognitive-complexity)
TEST_CASE("UniformRandomSolver is deterministic with a fixed seed", "[uniform]")
{
    const std::vector<Edge> edges = {{0, 1, 1.0}, {1, 2, 2.0}, {2, 3, 3.0}, {3, 0, 4.0}};
    const Graph graph = MakeGraph(4, edges);

    UniformRandomSolver solver1(42);
    UniformRandomSolver solver2(42);

    const auto result1 = solver1.Solve(graph);
    const auto result2 = solver2.Solve(graph);

    CHECK(result1.CutCost() == result2.CutCost());
}

TEST_CASE("UniformRandomSolver produces valid cut costs within graph bounds", "[uniform]")
{
    SECTION("Complete graph K4")
    {
        const std::vector<Edge> edges = {{0, 1, 1.0}, {0, 2, 1.0}, {0, 3, 1.0}, {1, 2, 1.0}, {1, 3, 1.0}, {2, 3, 1.0}};
        const Graph graph = MakeGraph(4, edges);

        UniformRandomSolver solver(123);
        const auto result = solver.Solve(graph);

        CHECK(result.CutCost() >= 0.0);
        CHECK(result.CutCost() <= 6.0);
    }

    SECTION("Graph with no edges")
    {
        const Graph graph = MakeGraph(3, {});
        UniformRandomSolver solver(42);
        const auto result = solver.Solve(graph);

        CHECK(result.CutCost() == 0.0);
    }

    SECTION("Single edge graph")
    {
        const Graph graph = MakeGraph(2, {{0, 1, 5.0}});
        UniformRandomSolver solver(42);
        const auto result = solver.Solve(graph);

        const double cost = result.CutCost();
        bool isValid = (cost == 0.0 || cost == 5.0);
        CHECK(isValid);
    }
}

TEST_CASE("UniformRandomSolver produces varied cuts across multiple seeds", "[uniform]")
{
    const std::vector<Edge> edges = {{0, 1, 1.0}, {1, 2, 2.0}, {2, 3, 3.0}, {3, 4, 4.0}, {4, 0, 5.0}};
    const Graph graph = MakeGraph(5, edges);

    const std::vector<unsigned> seeds = {1, 42, 100, 777, 999};
    std::vector<double> costs;
    costs.reserve(seeds.size());

    for (unsigned seed : seeds)
    {
        UniformRandomSolver solver(seed);
        costs.push_back(solver.Solve(graph).CutCost());
    }

    const bool hasVariation = std::any_of(costs.begin(), costs.end(), [&costs](double c) { return c != costs[0]; });

    CHECK(hasVariation);
}
// NOLINTEND(cppcoreguidelines-avoid-do-while, bugprone-chained-comparison, misc-use-anonymous-namespace,
// bugprone-throwing-static-initialization, cert-err58-cpp, readability-function-cognitive-complexity)

} // namespace MaxCut::Testing
