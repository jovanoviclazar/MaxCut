#include "Model/CutResult.hpp"
#include <vector>

namespace MaxCut
{
CutResult::CutResult(std::vector<int> &vectorA, std::vector<int> &vectorB, double cutCost)
    : m_vectorA(std::move(vectorA)), m_vectorB(std::move(vectorB)), m_cutCost(cutCost)
{
}
} // namespace MaxCut
