#include "stdafx.h"
#include "Scenario.h"


Scenario::Scenario(std::string i_name, std::string i_startingLocation)
  : name(std::move(i_name))
  , startingLocation(std::move(i_startingLocation))
{
}


void Scenario::pushFields()
{
  pushField("name", name);
  pushField("startingLocation", startingLocation);
}
