#pragma once

#include <vector>

namespace MaxCut
{
class CutResult
{
  private:
    std::vector<int> VectorA;
    std::vector<int> VectorB;

  public:
    CutResult(std::vector<int> &vectorA, std::vector<int> &vectorB);
};
} // namespace MaxCut
