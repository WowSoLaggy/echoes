#pragma once

#include "Fwd.h"
#include "Session.h"


class SessionLoader
{
public:
  static std::unique_ptr<Session> createNew(const std::string& i_scenarioName);
  static std::unique_ptr<Session> createNew(std::shared_ptr<Scenario> i_scenario);

  static std::unique_ptr<Session> load(const fs::path& i_path);

private:
  SessionLoader() = delete;
};
