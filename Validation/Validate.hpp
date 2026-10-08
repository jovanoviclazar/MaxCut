#pragma once

#include <string>

namespace MaxCut
{

class Validate
{
  public:
    template <typename T> static void ValidateNonNegative(T number, const std::string &fieldName);

    template <typename T> static void ValidatePositive(T number, const std::string &fieldName);
};

} // namespace MaxCut
