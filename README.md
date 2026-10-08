# MaxCut

## Requirements

- CMake >= 3.20
- Ninja
- A C++20 compiler (GCC or Clang)
- clang-format and clang-tidy (optional, for development)

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
| `-a` | `--algorithm` | Algorithm to run (`random`, `brute`, `gw`) | `random` |
| `-s` | `--seed` | Random seed for stochastic algorithms | `0` |

## Examples

### Run with defaults
./build/MaxCut

### Specify input graph and algorithm
./build/MaxCut -i data/graph.txt -a greedy

### Full options using long flags
./build/MaxCut --input data/graph.txt --output result.txt --algorithm random --seed 42

## Format

```bash
git ls-files -z '*.cpp' '*.hpp' | xargs -0 -r clang-format -i
```

## Check

```bash
git ls-files -z '*.cpp' '*.hpp' | xargs -0 -r clang-format --dry-run -Werror
git ls-files -z '*.cpp' | xargs -0 -r clang-tidy -p build
```

## Test

```bash
ctest --test-dir build --output-on-failure
```

## Clean

```bash
rm -rf build
```
