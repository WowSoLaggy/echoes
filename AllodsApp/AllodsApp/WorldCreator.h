#pragma once

#include "World.h"


class WorldCreator
{
public:
  static std::unique_ptr<World> createEmpty();
  static std::unique_ptr<World> createTest();
};
