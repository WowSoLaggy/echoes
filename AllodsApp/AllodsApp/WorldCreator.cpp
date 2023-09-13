#include "stdafx.h"
#include "WorldCreator.h"

#include "ObjectsSpawner.h"


World WorldCreator::createEmpty()
{
  World world;
  return world;
}


World WorldCreator::createTest()
{
  World world = createEmpty();

  const auto createStr = [&](const PrototypeName& i_protoName, const int x, const int y)
  {
    return ObjectsSpawner::spawnStructure(i_protoName, world, { x, y });
  };

  //

  createStr("Lattice", 0, 0);

  return world;
}

