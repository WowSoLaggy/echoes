#include "stdafx.h"
#include "WorldCreator.h"

#include "LocationCreator.h"


std::unique_ptr<World> WorldCreator::createTest()
{
  auto world = std::make_unique<World>();

  world->getLocations().push_back(LocationCreator::createTest());

  return world;
}
