#include "stdafx.h"
#include "SessionLoader.h"

#include "Scenario.h"
#include "Scenarios.h"
#include "WorldCreator.h"


std::unique_ptr<Session> SessionLoader::createNew(const std::string& i_scenarioName) const
{
  const auto& scenario = Scenarios::getScenario(i_scenarioName);
  return createNew(scenario);
}

std::unique_ptr<Session> SessionLoader::createNew(const Scenario& i_scenario) const
{
  auto session = std::make_unique<Session>();

  session->setWorld(WorldCreator::createTest());

  auto& startingLocation = SAFE_DEREF(session->getWorld()).getLocation(i_scenario.startingLocation);
  session->setCurrentLocation(&startingLocation);

  return session;
}
