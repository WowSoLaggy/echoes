#include "stdafx.h"
#include "SessionLoader.h"

#include "Scenario.h"
#include "Scenarios.h"
#include "World.h"
#include "WorldCreator.h"

#include <LaggySdk/JsonSerializer.h>


std::shared_ptr<Session> SessionLoader::createNew(const std::string& i_scenarioName)
{
  auto scenario = Scenarios::getScenario(i_scenarioName);
  return createNew(std::move(scenario));
}

std::shared_ptr<Session> SessionLoader::createNew(std::shared_ptr<Scenario> i_scenario)
{
  auto session = std::make_shared<Session>();

  session->setScenario(std::move(i_scenario));
  session->setWorld(WorldCreator::createTest());

  auto& startingLocation = SAFE_DEREF(session->getWorld()).getLocation(SAFE_DEREF(session->getScenario()).startingLocation);
  session->setCurrentLocation(&startingLocation);

  return session;
}


std::shared_ptr<Session> SessionLoader::load(const fs::path& i_path)
{
  auto session = std::make_shared<Session>();

  Sdk::JsonSerializer::deserialize(*session, i_path);

  // TODO: ae
  // Serialize current location instead of setting the starting one from scenario (it is obviously incorrect)
  auto& startingLocation = SAFE_DEREF(session->getWorld()).getLocation(SAFE_DEREF(session->getScenario()).startingLocation);
  session->setCurrentLocation(&startingLocation);

  return session;
}
