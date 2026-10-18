cmake_minimum_required(VERSION 3.28)

project(MaxCut LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "" FORCE)
set(CATCH_INSTALL_DOCS OFF CACHE BOOL "" FORCE)
set(CATCH_INSTALL_EXTRAS OFF CACHE BOOL "" FORCE)

include(FetchContent)

FetchContent_Declare(
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG        3.4.0
    SYSTEM
    EXCLUDE_FROM_ALL
)

FetchContent_Declare(
    clarabel_cpp
    GIT_REPOSITORY https://github.com/oxfordcontrol/Clarabel.cpp.git
    GIT_TAG        0de6259a3edfd5cc041ec42b2148599ce63e73cb
    SYSTEM
    EXCLUDE_FROM_ALL
)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
    SYSTEM
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(eigen clarabel_cpp Catch2)

add_executable(MaxCut
    Main.cpp
    Core/Core.cpp
    Model/Graph.cpp
    Model/CutResult.cpp
    IO/ArgumentParser.cpp
    IO/GraphParser.cpp
    IO/Output.cpp
    Solver/SolverFactory.cpp
    Solver/Algorithm/UniformRandomSolver.cpp
    Solver/Algorithm/BruteForceSolver.cpp
    Solver/Algorithm/GoemansWilliamsonSolver.cpp
    Solver/Algorithm/GreedySolver.cpp
)

target_compile_features(MaxCut PRIVATE cxx_std_20)
target_include_directories(MaxCut PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(MaxCut PRIVATE Eigen3::Eigen libclarabel_c_static)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(MaxCut PRIVATE -Wall -Wextra -Wpedantic)
endif()

enable_testing()

add_executable(UnitTests
    Tests/ArgumentParserTest.cpp
    Tests/GraphParserTest.cpp
    Tests/BruteForceSolverTest.cpp
    Tests/GreedySolverTest.cpp
    Solver/Algorithm/BruteForceSolver.cpp
    Solver/Algorithm/GreedySolver.cpp
    IO/ArgumentParser.cpp
    IO/GraphParser.cpp
    Model/Graph.cpp
    Model/CutResult.cpp
)

target_compile_features(UnitTests PRIVATE cxx_std_20)
target_include_directories(UnitTests PRIVATE ${PROJECT_SOURCE_DIR})
target_link_libraries(UnitTests PRIVATE Catch2::Catch2WithMain)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(UnitTests PRIVATE -Wall -Wextra -Wpedantic)
endif()

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(UnitTests
    TEST_PREFIX "UnitTests::"
    DISCOVERY_MODE PRE_TEST
    PROPERTIES LABELS "unit"
)
