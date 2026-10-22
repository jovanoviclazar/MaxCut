#include "Solver/Algorithm/GoemansWilliamsonSolver.hpp"
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

double Solve(int vertices, const std::vector<Edge> &edges, unsigned seed = 42)
{
    const Graph graph = MakeGraph(vertices, edges);
    GoemansWilliamsonSolver solver(seed);
    return solver.Solve(graph).CutCost();
}

} // namespace

// NOLINTBEGIN(cppcoreguidelines-avoid-do-while, bugprone-chained-comparison, misc-use-anonymous-namespace,
// bugprone-throwing-static-initialization, cert-err58-cpp, readability-function-cognitive-complexity)
TEST_CASE("GoemansWilliamsonSolver is deterministic with a fixed seed", "[gw]")
{
    const std::vector<Edge> edges = {{0, 1, 1.0}, {1, 2, 2.0}, {2, 3, 3.0}, {3, 0, 4.0}};
    const Graph graph = MakeGraph(4, edges);

    GoemansWilliamsonSolver solver1(1337);
    GoemansWilliamsonSolver solver2(1337);

    const double cost1 = solver1.Solve(graph).CutCost();
    const double cost2 = solver2.Solve(graph).CutCost();

    CHECK(cost1 == cost2);
}

TEST_CASE("GoemansWilliamsonSolver finds valid cuts on standard graphs", "[gw]")
{
    SECTION("Single edge")
    {
        CHECK(Solve(2, {{0, 1, 5.0}}, 42) == 5.0);
    }

    SECTION("Path of three vertices")
    {
        CHECK(Solve(3, {{0, 1, 1.0}, {1, 2, 1.0}}, 42) == 2.0);
    }

    SECTION("Even cycle (bipartite graph)")
    {
        CHECK(Solve(4, {{0, 1, 1.0}, {1, 2, 1.0}, {2, 3, 1.0}, {3, 0, 1.0}}, 42) == 4.0);
    }

    SECTION("Complete graph K4")
    {
        CHECK(Solve(4, {{0, 1, 1.0}, {0, 2, 1.0}, {0, 3, 1.0}, {1, 2, 1.0}, {1, 3, 1.0}, {2, 3, 1.0}}, 42) == 4.0);
    }

    SECTION("No edges")
    {
        CHECK(Solve(3, {}, 42) == 0.0);
    }
}

TEST_CASE("GoemansWilliamsonSolver produces varied cuts across multiple seeds", "[gw]")
{
    const std::vector<Edge> edges = {{0, 1, 1.0}, {1, 2, 2.0}, {2, 3, 3.0}, {3, 4, 4.0}, {4, 0, 5.0}};
    const Graph graph = MakeGraph(5, edges);

    const std::vector<unsigned> seeds = {1, 42, 100, 777, 999};
    std::vector<double> costs;
    costs.reserve(seeds.size());

    for (unsigned seed : seeds)
    {
        GoemansWilliamsonSolver solver(seed);
        costs.push_back(solver.Solve(graph).CutCost());
    }

    const bool hasVariation = std::any_of(costs.begin(), costs.end(), [&costs](double c) { return c != costs[0]; });

    CHECK(hasVariation);
}
// NOLINTEND(cppcoreguidelines-avoid-do-while, bugprone-chained-comparison, misc-use-anonymous-namespace,
// bugprone-throwing-static-initialization, cert-err58-cpp, readability-function-cognitive-complexity)

} // namespace MaxCut::Testing
