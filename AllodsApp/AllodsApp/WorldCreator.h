#pragma once

#include "World.h"


class WorldCreator
{
public:
  static std::unique_ptr<World> createTest();

private:
  WorldCreator() = delete;
};
