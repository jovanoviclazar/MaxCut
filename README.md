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
./build/MaxCut <arguments>
```

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
