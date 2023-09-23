#include "stdafx.h"
#include "WorldCreator.h"

#include "ObjectsSpawner.h"


std::unique_ptr<World> WorldCreator::createEmpty()
{
  return std::make_unique<World>();
}


std::unique_ptr<World> WorldCreator::createTest()
{
  auto world = createEmpty();

  const auto createStr = [&](const PrototypeName& i_protoName, const int x, const int y)
  {
    return ObjectsSpawner::spawnStructure(i_protoName, *world, { x, y });
  };

  //

  createStr("Lattice", 8, 5);

  return world;
}

