#include "stdafx.h"
#include "LocationCreator.h"

#include "Avatar.h"
#include "Constants.h"
#include "Gases.h"
#include "Location.h"
#include "Mount.h"
#include "Object.h"
#include "ObjectsSpawner.h"
#include "Structure.h"
#include "TileUtils.h"
#include "Units.h"


namespace
{
  template <typename T>
  T setDefaultTemperature(T i_obj)
  {
    i_obj->setTemperature(Constants::DefaultEntityTemperature);
    return i_obj;
  }
} // anonym NS


std::shared_ptr<Location> LocationCreator::createTest()
{
  auto location = std::make_unique<Location>();
  location->setName("Test Location");

  const auto createStr = [&](const PrototypeName& i_protoName, const int x, const int y)
  {
    return setDefaultTemperature(ObjectsSpawner::spawnStructure(i_protoName, *location, { x, y }));
  };

  const auto createMount = [&](
    const PrototypeName& i_protoName, Structure& i_structure, const FixtureLocation i_location)
  {
    return setDefaultTemperature(ObjectsSpawner::spawnMount(i_protoName, i_structure, i_location));
  };

  const auto createObject = [&](
    const PrototypeName& i_protoName, Sdk::Vector2I i_position)
  {
    return setDefaultTemperature(ObjectsSpawner::spawnObject(i_protoName, *location, std::move(i_position)));
  };

  const auto createAvatar = [&](
    const PrototypeName& i_protoName, Sdk::Vector2I i_position)
  {
    return setDefaultTemperature(ObjectsSpawner::spawnAvatar(i_protoName, *location, std::move(i_position)));
  };

  // Base

  for (int x = 5; x <= 15; ++x)
  {
    createStr("Lattice", x, 2);
    createStr("Lattice", x, 8);
  }

  for (int y = 3; y <= 7; ++y)
  {
    createStr("Lattice", 5, y);
    createStr("Lattice", 15, y);
  }

  for (int x = 6; x <= 14; ++x)
  {
    for (int y = 3; y <= 7; ++y)
      createStr("Plating", x, y);
  }

  for (int x = 7; x <= 13; ++x)
  {
    for (int y = 4; y <= 6; ++y)
      createStr("Floor", x, y);
  }

  for (int x = 6; x <= 14; ++x)
  {
    createStr("Wall", x, 3);
    if (x != 8)
      createStr("Wall", x, 7);
  }

  for (int y = 4; y <= 6; ++y)
  {
    createStr("Wall", 6, y);
    if (y != 6)
      createStr("Wall", 10, y);
    createStr("Wall", 14, y);
  }

  createStr("Floor", 8, 7);
  createStr("Door", 8, 7);
  createStr("Door", 10, 6);

  // Atmosphere

  for (int y = 4; y <= 6; ++y)
  {
    for (int x = 7; x <= 9; ++x)
    {
      //SAFE_DEREF(location->getOrCreateTile({ x, y }).getGasUnitThd().getGasUnit()).addGas(static_cast<Dx::thd::GasId>(Gas::Oxygen), (int)Constants::PaInOneAtm);
      //location->getOrCreateTile({ x, y }).getGasUnitThd().setTemperature(Units::celsiusToKelvin(22));
    }
  }

  /*SAFE_DEREF(location->getOrCreateTile({ 12, 5 }).getGasUnitThd().getGasUnit()).addGas(static_cast<Dx::thd::GasId>(Gas::CarbonDioxide), (int)Constants::PaInOneAtm);
  for (int y = 4; y <= 6; ++y)
  {
    for (int x = 11; x <= 13; ++x)
    {
      if (x != 12 || y != 5)
        SAFE_DEREF(location->getOrCreateTile({ x, y }).getGasUnitThd().getGasUnit()).addGas(static_cast<Dx::thd::GasId>(Gas::Oxygen), (int)Constants::PaInOneAtm);
      
      location->getOrCreateTile({ x, y }).getGasUnitThd().setTemperature(Units::celsiusToKelvin(22));
    }
  }*/

  for (int y = 4; y <= 6; ++y)
  {
    for (int x = 11; x <= 13; ++x)
    {
      SAFE_DEREF(location->getOrCreateTile({ x, y }).getGasUnitThd().getGasUnit()).addGas(static_cast<Dx::thd::GasId>(Gas::Oxygen), (int)Constants::PaInOneAtm * 8 / 9);
      SAFE_DEREF(location->getOrCreateTile({ x, y }).getGasUnitThd().getGasUnit()).addGas(static_cast<Dx::thd::GasId>(Gas::CarbonDioxide), (int)Constants::PaInOneAtm * 1 / 9);

      location->getOrCreateTile({ x, y }).getGasUnitThd().setTemperature(Units::celsiusToKelvin(22));
    }
  }

  /*SAFE_DEREF(location->getOrCreateTile({ 12, 5 }).getGasUnitThd().getGasUnit()).addGas(static_cast<Dx::thd::GasId>(Gas::Oxygen), (int)Constants::PaInOneAtm * 19);
  location->getOrCreateTile({ 12, 5 }).getGasUnitThd().setTemperature(Units::celsiusToKelvin(100));*/

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

