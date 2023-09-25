#pragma once

#include "Fwd.h"


class Scenarios
{
public:
  static const Scenario& getScenario(const std::string& i_name);

private:
  Scenarios() = delete;
};
