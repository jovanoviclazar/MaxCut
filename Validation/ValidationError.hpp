#pragma once

#include <stdexcept>
#include <string>

namespace MaxCut
{

class ValidationError : public std::runtime_error
{
  public:
    ValidationError(const std::string &message) : std::runtime_error("Validation Error: " + message)
    {
    }
};

class InvalidGraphError : public ValidationError
{
  public:
    InvalidGraphError(const std::string &details) : ValidationError("Invalid Graph - " + details)
    {
    }
};

class InvalidCutError : public ValidationError
{
  public:
    InvalidCutError(const std::string &details) : ValidationError("Invalid Cut Result - " + details)
    {
    }
};

} // namespace MaxCut
