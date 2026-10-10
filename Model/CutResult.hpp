#pragma once

#include <vector>

namespace MaxCut
{
class CutResult
{
  private:
    std::vector<size_t> m_vectorA;
    std::vector<size_t> m_vectorB;
    double m_cutCost;

  public:
    CutResult(std::vector<size_t> &vectorA, std::vector<size_t> &vectorB, double cutCost);
    const std::vector<size_t> &VectorA() const;
    const std::vector<size_t> &VectorB() const;
    double CutCost() const;
};
} // namespace MaxCut
