#include "stdafx.h"
#include "LocationCreator.h"

#include "ObjectsSpawner.h"
#include "Structure.h"


std::unique_ptr<Location> LocationCreator::createTest()
{
  auto location = std::make_unique<Location>();
  location->setName("Test Location");

  const auto createStr = [&](const PrototypeName& i_protoName, const int x, const int y)
  {
    return ObjectsSpawner::spawnStructure(i_protoName, *location, { x, y });
  };

  //

  for (int x = 5; x <= 11; ++x)
  {
    createStr("Lattice", x, 2);
    createStr("Lattice", x, 8);
  }

  for (int y = 3; y <= 7; ++y)
  {
    createStr("Lattice", 5, y);
    createStr("Lattice", 11, y);
  }

  for (int x = 6; x <= 10; ++x)
  {
    for (int y = 3; y <= 7; ++y)
      createStr("Plating", x, y);
  }

  for (int x = 7; x <= 9; ++x)
  {
    for (int y = 4; y <= 6; ++y)
      createStr("Floor", x, y);
  }

  for (int x = 6; x <= 10; ++x)
  {
    createStr("Wall", x, 3);
    if (x != 8)
      createStr("Wall", x, 7);
  }

  for (int y = 4; y <= 6; ++y)
  {
    createStr("Wall", 6, y);
    createStr("Wall", 10, y);
  }

  createStr("Floor", 8, 7);
  auto& door = *createStr("Door", 8, 7);

  return location;
}

