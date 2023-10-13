#include "stdafx.h"
#include "Scenarios.h"

#include "Scenario.h"


const Scenario& Scenarios::getScenario(const std::string& i_name)
{
  static const std::vector<Scenario> ScenarioList{
    { "Test Scenario", "Test Location" }
  };

  const auto it = std::find_if(ScenarioList.begin(), ScenarioList.end(), [&](const auto& i_scenario) {
    return i_scenario.name == i_name; });
  CONTRACT_EXPECT(it != ScenarioList.end());

  return *it;
}
