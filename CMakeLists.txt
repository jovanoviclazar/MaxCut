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
set(CLARABEL_FEATURE_SDP "sdp-openblas" CACHE STRING "" FORCE)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5) 

include(FetchContent)

FetchContent_Declare( 
    eigen
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    GIT_TAG        3.4.0
    SYSTEM
    EXCLUDE_FROM_ALL
    FIND_PACKAGE_ARGS 3.4 NAMES Eigen3
)

FetchContent_Declare(
    clarabel_cpp
    GIT_REPOSITORY https://github.com/oxfordcontrol/Clarabel.cpp.git
    GIT_TAG        0de6259a3edfd5cc041ec42b2148599ce63e73cb
    SYSTEM
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(eigen clarabel_cpp)

add_library(maxcut_warnings INTERFACE)
target_compile_options(maxcut_warnings INTERFACE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall;-Wextra;-Wpedantic>
)

add_library(maxcut_base STATIC
    Model/Graph.cpp
    Model/CutResult.cpp
    IO/ArgumentParser.cpp
    IO/GraphParser.cpp
    IO/Output.cpp
    Solver/Algorithm/UniformRandomSolver.cpp
    Solver/Algorithm/BruteForceSolver.cpp
    Solver/Algorithm/GreedySolver.cpp
)
target_include_directories(maxcut_base PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(maxcut_base PRIVATE maxcut_warnings)

add_executable(MaxCut
    Main.cpp
    Core/Core.cpp
    Solver/SolverFactory.cpp
    Solver/Algorithm/GoemansWilliamsonSolver.cpp
)
target_link_libraries(MaxCut PRIVATE maxcut_base maxcut_warnings Eigen3::Eigen libclarabel_c_static)
target_compile_definitions(MaxCut PRIVATE CLARABEL_FEATURE_SDP)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2
    SYSTEM
    EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(UnitTests
    Tests/ArgumentParserTest.cpp
    Tests/GraphParserTest.cpp
    Tests/BruteForceSolverTest.cpp
    Tests/GreedySolverTest.cpp
)

target_link_libraries(UnitTests PRIVATE maxcut_base maxcut_warnings Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(UnitTests
    TEST_PREFIX "UnitTests::"
    DISCOVERY_MODE PRE_TEST
    PROPERTIES LABELS "unit"
)
