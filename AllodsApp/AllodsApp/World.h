#pragma once

#include "Fwd.h"
#include "Location.h"

#include <LaggySdk/ISerializable.h>


class World : public Sdk::ISerializable
{
public:
  virtual void pushFields() override;

  Location& getLocation(const std::string& i_name) const;

  Locations& getLocations();
  const Locations& getLocations() const;

private:
  Locations d_locations;
};
