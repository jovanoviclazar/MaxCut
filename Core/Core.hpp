#pragma once

#include "Model/Configuration.hpp"

namespace MaxCut
{

class Core
{
  public:
    Core(Configuration &config);

    int Run() const;

  private:
    Configuration m_config;
};

} // namespace MaxCut
