#pragma once

#include "Fwd.h"


class WorldCreator
{
public:
  static std::shared_ptr<World> createTest();

private:
  WorldCreator() = delete;
};
