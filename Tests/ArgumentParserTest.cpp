#include "IO/ArgumentParser.hpp"
#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include <string>
#include <vector>

namespace MaxCut::Testing
{

namespace
{
Configuration ParseArgs(const std::vector<std::string> &args)
{
    std::vector<std::string> args_copy = args;
    std::vector<char *> argv;
    argv.reserve(args_copy.size());

    for (auto &arg : args_copy)
    {
        argv.push_back(arg.data());
    }

    return ArgumentParser::Parse(static_cast<int>(argv.size()), argv.data());
}

} // namespace

TEST_CASE("ArgumentParser defaults", "[cli]")
{
    const Configuration config = ParseArgs({"MaxCut"});

    REQUIRE(config.inputPath == "Dummy.txt");
    REQUIRE_FALSE(config.outputPath.has_value());
    REQUIRE(config.algorithm == "random");
    REQUIRE(config.seed == 0U);
}

TEST_CASE("ArgumentParser parses short flags", "[cli]")
{
    const Configuration config = ParseArgs({"MaxCut", "-i", "graph.txt", "-o", "out.txt", "-a", "greedy", "-s", "42"});

    CHECK(config.inputPath == "graph.txt");
    REQUIRE(config.outputPath.has_value());
    CHECK(config.outputPath.value() == "out.txt");
    CHECK(config.algorithm == "greedy");
    CHECK(config.seed == 42U);
}

TEST_CASE("ArgumentParser parses long flags", "[cli]")
{
    const Configuration config = ParseArgs(
        {"MaxCut", "--input", "data/large.txt", "--output", "results/res.txt", "--algorithm", "gw", "--seed", "12345"});

    CHECK(config.inputPath == "data/large.txt");
    REQUIRE(config.outputPath.has_value());
    CHECK(config.outputPath.value() == "results/res.txt");
    CHECK(config.algorithm == "gw");
    CHECK(config.seed == 12345U);
}

TEST_CASE("ArgumentParser retains default values for omitted flags", "[cli]")
{
    const Configuration config = ParseArgs({"MaxCut", "-i", "custom_graph.txt"});

    CHECK(config.inputPath == "custom_graph.txt");
    CHECK_FALSE(config.outputPath.has_value());
    CHECK(config.algorithm == "random");
    CHECK(config.seed == 0U);
}

TEST_CASE("ArgumentParser error handling", "[cli]")
{
    SECTION("Throws on unknown flag")
    {
        REQUIRE_THROWS_AS(ParseArgs({"MaxCut", "-z"}), std::invalid_argument);
    }

    SECTION("Throws on missing argument value")
    {
        REQUIRE_THROWS_AS(ParseArgs({"MaxCut", "-i"}), std::invalid_argument);
    }

    SECTION("Throws on invalid seed format")
    {
        REQUIRE_THROWS_AS(ParseArgs({"MaxCut", "-s", "not_a_number"}), std::invalid_argument);
    }
}

} // namespace MaxCut::Testing
