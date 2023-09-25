#pragma once

#include "Location.h"


class World
{
public:
  Location& getLocation(const std::string& i_name) const;

  std::vector<std::unique_ptr<Location>>& getLocations();
  const std::vector<std::unique_ptr<Location>>& getLocations() const;

private:
  std::vector<std::unique_ptr<Location>> d_locations;
};
