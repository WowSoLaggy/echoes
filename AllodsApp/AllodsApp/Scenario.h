#pragma once

#include <LaggySdk/ISerializable.h>


struct Scenario : public Sdk::ISerializable
{
  Scenario(std::string i_name, std::string i_startingLocation);

  virtual void pushFields() override;

  std::string name;
  std::string startingLocation;
};
