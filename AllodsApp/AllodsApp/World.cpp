#include "stdafx.h"
#include "World.h"


void World::pushFields()
{
  pushVector("locations", d_locations);
}


Location& World::getLocation(const std::string& i_name) const
{
  const auto it = std::find_if(d_locations.begin(), d_locations.end(), [&](const auto& locationPtr) {
    return locationPtr->getName() == i_name; });
  CONTRACT_EXPECT(it != d_locations.end());

  return **it;
}


Locations& World::getLocations()
{
  return d_locations;
}

const Locations& World::getLocations() const
{
  return d_locations;
}
