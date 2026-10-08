cmake_minimum_required(VERSION 3.20)

project(MaxCut LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(MaxCut
    Main.cpp

    Core/Core.cpp

    Model/Graph.cpp
    Model/CutResult.cpp

    IO/ArgumentParser.cpp
    IO/GraphParser.cpp
    IO/Output.cpp

    Solver/SolverFactory.cpp
    Solver/Algorithm/BasicRandomSolver.cpp
    Solver/Algorithm/BruteForceSolver.cpp
    Solver/Algorithm/GoemansWilliamsonSolver.cpp
)

target_compile_features(MaxCut PRIVATE cxx_std_20)
target_include_directories(MaxCut PRIVATE ${CMAKE_SOURCE_DIR})

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(MaxCut PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()
