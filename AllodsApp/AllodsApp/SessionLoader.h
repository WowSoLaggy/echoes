#pragma once

#include "Fwd.h"
#include "Session.h"


class SessionLoader
{
public:
  static std::unique_ptr<Session> createNew(const std::string& i_scenarioName);
  static std::unique_ptr<Session> createNew(const Scenario& i_scenario);

private:
  SessionLoader() = delete;
};
