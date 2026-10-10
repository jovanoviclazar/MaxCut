// Tests/BruteForceSolverTest.cpp
#include "Solver/Algorithm/BruteForceSolver.hpp"
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

// Independent reference: tries every subset with a bitmask.
double ReferenceMaxCut(int vertices, const std::vector<Edge> &edges)
{
    double best = 0.0;
    for (unsigned mask = 0; mask < (1U << vertices); ++mask)
    {
        double weight = 0.0;
        for (const auto &[u, v, w] : edges)
        {
            if (((mask >> u) & 1U) != ((mask >> v) & 1U))
            {
                weight += w;
            }
        }
        best = std::max(best, weight);
    }
    return best;
}

double Solve(int vertices, const std::vector<Edge> &edges)
{
    const Graph graph = MakeGraph(vertices, edges);
    BruteForceSolver solver;
    return solver.Solve(graph).CutCost();
}

} // namespace

// NOLINTBEGIN(cppcoreguidelines-avoid-do-while, bugprone-chained-comparison, misc-use-anonymous-namespace,
// bugprone-throwing-static-initialization, cert-err58-cpp, readability-function-cognitive-complexity)
TEST_CASE("BruteForceSolver finds known optimal cuts", "[brute]")
{
    SECTION("Single edge")
    {
        CHECK(Solve(2, {{0, 1, 5.0}}) == Catch::Approx(5.0));
    }

    SECTION("Path of three vertices")
    {
        CHECK(Solve(3, {{0, 1, 1.0}, {1, 2, 1.0}}) == Catch::Approx(2.0));
    }

    SECTION("Unit triangle: only two of three edges can be cut")
    {
        CHECK(Solve(3, {{0, 1, 1.0}, {1, 2, 1.0}, {0, 2, 1.0}}) == Catch::Approx(2.0));
    }

    SECTION("Weighted triangle: isolate the heaviest vertex")
    {
        // Vertex 2 has incident weight 3 + 2 = 5, the largest.
        CHECK(Solve(3, {{0, 1, 1.0}, {1, 2, 3.0}, {0, 2, 2.0}}) == Catch::Approx(5.0));
    }

    SECTION("Even cycle is bipartite: all edges cut")
    {
        CHECK(Solve(4, {{0, 1, 1.0}, {1, 2, 1.0}, {2, 3, 1.0}, {3, 0, 1.0}}) == Catch::Approx(4.0));
    }

    SECTION("Complete graph K4: a 2-2 split cuts four edges")
    {
        CHECK(Solve(4, {{0, 1, 1.0}, {0, 2, 1.0}, {0, 3, 1.0}, {1, 2, 1.0}, {1, 3, 1.0}, {2, 3, 1.0}}) ==
              Catch::Approx(4.0));
    }

    SECTION("No edges")
    {
        CHECK(Solve(3, {}) == Catch::Approx(0.0));
    }
}

TEST_CASE("BruteForceSolver matches an independent reference", "[brute]")
{
    const std::vector<Edge> edges = {{0, 1, 2.5}, {0, 3, 1.0}, {1, 2, 4.0}, {1, 4, 0.5},
                                     {2, 3, 3.0}, {2, 4, 1.5}, {3, 4, 2.0}};

    CHECK(Solve(5, edges) == Catch::Approx(ReferenceMaxCut(5, edges)));
}
// NOLINTEND(cppcoreguidelines-avoid-do-while, bugprone-chained-comparison, misc-use-anonymous-namespace,
// bugprone-throwing-static-initialization, cert-err58-cpp, readability-function-cognitive-complexity)
} // namespace MaxCut::Testing
