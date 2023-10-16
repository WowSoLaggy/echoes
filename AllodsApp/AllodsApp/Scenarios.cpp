#include "stdafx.h"
#include "Scenarios.h"

#include "Scenario.h"


std::shared_ptr<Scenario> Scenarios::getScenario(const std::string& i_name)
{
  static const std::vector<std::shared_ptr<Scenario>> ScenarioList{
    std::make_shared<Scenario>("Test Scenario", "Test Location"),
  };

  const auto it = std::find_if(ScenarioList.begin(), ScenarioList.end(), [&](const auto& i_scenario) {
    return SAFE_DEREF(i_scenario).name == i_name; });
  CONTRACT_EXPECT(it != ScenarioList.end());

  return *it;
}
