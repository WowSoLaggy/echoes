#pragma once

#include "Fwd.h"
#include "Session.h"


class SessionLoader
{
public:
  std::unique_ptr<Session> createNew(const std::string& i_scenarioName) const;
  std::unique_ptr<Session> createNew(const Scenario& i_scenario) const;
};
