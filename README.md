# MaxCut

Command-line tool for the Maximum Cut problem with several solvers: uniform random, brute force, greedy, and Goemans-Williamson.

## Requirements

- CMake >= 3.28
- Ninja
- A C++20 compiler (GCC or Clang)
- Git
- Rust toolchain (`rustc` and `cargo`), needed to build Clarabel
- Internet access on the first configure (dependencies are downloaded with CMake `FetchContent`)

## Build

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

## Run

```bash
./build/MaxCut [-i input_path] [-o output_path] [-a algorithm] [-s seed]
```

| Short | Long | Description | Default |
| --- | --- | --- | --- |
| `-i` | `--input` | Path to the graph input file | `Dummy.txt` |
| `-o` | `--output` | Optional path to write output results | *(None)* |
| `-a` | `--algorithm` | Algorithm to run (`random`, `brute`, `greedy`, `gw`) | `random` |
| `-s` | `--seed` | Random seed for stochastic algorithms | `12345` |

## Examples

Run with defaults:

```bash
./build/MaxCut
```

Specify input graph and algorithm:

```bash
./build/MaxCut -i data/graph.txt -a greedy
```

Full options using long flags:

```bash
./build/MaxCut --input data/graph.txt --output result.txt --algorithm random --seed 42
```

## Test

Only the project's own unit tests are registered with CTest (label `unit`):

```bash
ctest --test-dir build --output-on-failure -L unit
```

Or run the test binary directly:

```bash
./build/UnitTests
```

## Clean

```bash
rm -rf build
```

## Third-party libraries

Dependencies are fetched automatically at configure time and are not vendored in this repository. All credit goes to their authors.

| Library | Used for | License | Source |
| --- | --- | --- | --- |
| [Eigen](https://eigen.tuxfamily.org) 3.4.0 | Linear algebra | MPL-2.0 | https://gitlab.com/libeigen/eigen |
| [Clarabel.cpp](https://github.com/oxfordcontrol/Clarabel.cpp) | C++ interface to the Clarabel interior-point conic solver, used by the Goemans-Williamson solver | Apache-2.0 | https://github.com/oxfordcontrol/Clarabel.cpp |
| [Clarabel.rs](https://github.com/oxfordcontrol/Clarabel.rs) | Rust solver wrapped by Clarabel.cpp (fetched as its submodule) | Apache-2.0 | https://github.com/oxfordcontrol/Clarabel.rs |
| [Catch2](https://github.com/catchorg/Catch2) v3.5.2 | Unit testing framework (tests only) | BSL-1.0 | https://github.com/catchorg/Catch2 |

If you use the Clarabel solver in academic work, please cite it as requested in the [Clarabel documentation](https://clarabel.org).
