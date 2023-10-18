#pragma once

#include "Fwd.h"


class LocationCreator
{
public:
  static std::shared_ptr<Location> createTest();

private:
  LocationCreator() = delete;
};
