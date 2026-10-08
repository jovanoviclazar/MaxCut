#include "Model/CutResult.hpp"
#include <vector>

namespace MaxCut
{
CutResult::CutResult(std::vector<int> &vectorA, std::vector<int> &vectorB, double cutCost)
    : m_vectorA(std::move(vectorA)), m_vectorB(std::move(vectorB)), m_cutCost(cutCost)
{
}
const std::vector<int> &CutResult::VectorA() const
{
    return m_vectorA;
}
const std::vector<int> &CutResult::VectorB() const
{
    return m_vectorB;
}
double CutResult::CutCost() const
{
    return m_cutCost;
}
} // namespace MaxCut
