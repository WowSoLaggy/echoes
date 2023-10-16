#pragma once

#include "Fwd.h"


class Scenarios
{
public:
  static std::shared_ptr<Scenario> getScenario(const std::string& i_name);

private:
  Scenarios() = delete;
};
