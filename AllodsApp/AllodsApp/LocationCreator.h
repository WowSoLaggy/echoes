#pragma once

#include "Location.h"


class LocationCreator
{
public:
  static std::unique_ptr<Location> createEmpty();
  static std::unique_ptr<Location> createTest();
};
