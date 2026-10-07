#include "Model/CutResult.hpp"
#include <vector>

namespace MaxCut
{
CutResult::CutResult(std::vector<int> &vectorA, std::vector<int> &vectorB)
    : VectorA(std::move(vectorA)), VectorB(std::move(vectorB))
{
}
} // namespace MaxCut
