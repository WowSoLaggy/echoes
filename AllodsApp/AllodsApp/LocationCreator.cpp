#include "stdafx.h"
#include "LocationCreator.h"

#include "Constants.h"
#include "Gases.h"
#include "Location.h"
#include "Mount.h"
#include "ObjectsSpawner.h"
#include "Structure.h"
#include "TileUtils.h"
#include "Units.h"


std::shared_ptr<Location> LocationCreator::createTest()
{
  auto location = std::make_unique<Location>();
  location->setName("Test Location");

  const auto createStr = [&](const PrototypeName& i_protoName, const int x, const int y)
  {
    location->getOrCreateTile({ x, y }).setT(Units::celsiusToKelvin(22));
    return ObjectsSpawner::spawnStructure(i_protoName, *location, { x, y });
  };

  const auto createMount = [&](
    const PrototypeName& i_protoName, Structure& i_structure, const FixtureLocation i_location)
  {
    return ObjectsSpawner::spawnMount(i_protoName, i_structure, i_location);
  };

  const auto createObject = [&](
    const PrototypeName& i_protoName, Sdk::Vector2I i_position)
  {
    return ObjectsSpawner::spawnObject(i_protoName, *location, std::move(i_position));
  };

  const auto createAvatar = [&](
    const PrototypeName& i_protoName, Sdk::Vector2I i_position)
  {
    return ObjectsSpawner::spawnAvatar(i_protoName, *location, std::move(i_position));
  };

  // Base

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

  // Atmosphere

  location->getOrCreateTile({ 8, 5 }).getUnit().addGas(static_cast<Dx::thd::GasId>(Gas::Oxygen), (int)Constants::PaInOneAtm * 9);


  // Interior

  {
    auto& wallN = SAFE_DEREF(location->getOrCreateTile({ 8, 3 }).getStructure(Layer::Wall));
    createMount("Lamp", wallN, FixtureLocation::Bottom);
  }
  {
    auto& wallE = SAFE_DEREF(location->getOrCreateTile({ 10, 5 }).getStructure(Layer::Wall));
    createMount("Lamp", wallE, FixtureLocation::Left);
  }
  {
    auto& wallW = SAFE_DEREF(location->getOrCreateTile({ 6, 5 }).getStructure(Layer::Wall));
    createMount("Lamp", wallW, FixtureLocation::Right);
  }
  {
    auto& wallS1 = SAFE_DEREF(location->getOrCreateTile({ 7, 7 }).getStructure(Layer::Wall));
    auto& wallS2 = SAFE_DEREF(location->getOrCreateTile({ 9, 7 }).getStructure(Layer::Wall));
    createMount("Lamp", wallS1, FixtureLocation::Top);
    createMount("Lamp", wallS2, FixtureLocation::Top);
  }

  createStr("Crate", 9, 4);

  createObject("Lamp_bulb", TileUtils::getTileCenter({ 8, 5 }));

  createAvatar("Man", TileUtils::getTileCenter({ 7, 5 }));

  return location;
}

