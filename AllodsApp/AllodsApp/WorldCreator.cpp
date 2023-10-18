#include "stdafx.h"
#include "WorldCreator.h"

#include "LocationCreator.h"
#include "World.h"


std::shared_ptr<World> WorldCreator::createTest()
{
  auto world = std::make_shared<World>();

  world->getLocations().push_back(LocationCreator::createTest());

  return world;
}
