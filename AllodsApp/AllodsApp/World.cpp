#include "stdafx.h"
#include "World.h"


void World::pushFields()
{
  for (const auto& locationPtr : d_locations)
    pushObject("location", SAFE_DEREF(locationPtr));
}


Location& World::getLocation(const std::string& i_name) const
{
  const auto it = std::find_if(d_locations.begin(), d_locations.end(), [&](const auto& locationPtr) {
    return locationPtr->getName() == i_name; });
  CONTRACT_EXPECT(it != d_locations.end());

  return **it;
}


std::vector<std::unique_ptr<Location>>& World::getLocations()
{
  return d_locations;
}

const std::vector<std::unique_ptr<Location>>& World::getLocations() const
{
  return d_locations;
}
