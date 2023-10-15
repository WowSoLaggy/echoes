#pragma once

#include "Location.h"

#include <LaggySdk/ISerializable.h>


class World : public Sdk::ISerializable
{
public:
  virtual void pushFields() override;

  Location& getLocation(const std::string& i_name) const;

  std::vector<std::unique_ptr<Location>>& getLocations();
  const std::vector<std::unique_ptr<Location>>& getLocations() const;

private:
  std::vector<std::unique_ptr<Location>> d_locations;
};
