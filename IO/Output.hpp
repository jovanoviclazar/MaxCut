#pragma once

#include "Model/CutResult.hpp"
#include <ostream>
namespace MaxCut
{
class Output
{
  public:
    static void Write(std::ostream &output, const CutResult &cut);
    static void WriteToFile(const std::string &filePath, const CutResult &cut);
};
std::ostream &operator<<(std::ostream &output, const CutResult &cut);
} // namespace MaxCut
