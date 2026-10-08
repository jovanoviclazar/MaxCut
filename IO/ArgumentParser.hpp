#pragma once

#include <Model/Configuration.hpp>
#include <string>
#include <vector>

namespace MaxCut
{
class ArgumentParser
{
  private:
    static std::vector<std::string> ConvertArgs(int argc, char **argv);

  public:
    static Configuration Parse(int argc, char **argv);
};
} // namespace MaxCut
