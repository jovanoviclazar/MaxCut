#pragma once

#include <vector>

namespace MaxCut
{
class CutResult
{
  private:
    std::vector<int> m_vectorA;
    std::vector<int> m_vectorB;
    double m_cutCost;

  public:
    CutResult(std::vector<int> &vectorA, std::vector<int> &vectorB, double cutCost);
    std::vector<int> &VectorA() const;
    std::vector<int> &VectorB() const;
    double CutCost() const;
};
} // namespace MaxCut
