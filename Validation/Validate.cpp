#include "Validation/Validate.hpp"
#include "Validation/ValidationError.hpp"

namespace MaxCut
{
template <typename T> void Validate::ValidateNonNegative(T number, const std::string &fieldName)
{
    if (number < 0)
    {
        throw ValidationError(fieldName + " cannot be negative.");
    }
}

template <typename T> void Validate::ValidatePositive(T number, const std::string &fieldName)
{
    if (number <= 0)
    {
        throw ValidationError(fieldName + " must be strictly positive.");
    }
}
} // namespace MaxCut
