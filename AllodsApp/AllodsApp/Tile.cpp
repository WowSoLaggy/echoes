#include "stdafx.h"
#include "Tile.h"

#include "Avatar.h"
#include "Constants.h"
#include "Mount.h"
#include "Object.h"
#include "Prototypes.h"
#include "Structure.h"

#include <LaggySdk/JsonSerializer.h>


void Tile::pushFields()
{
  for (auto& [layer, structurePtr] : d_layers)
    pushObject(LayerStr::toString(layer), SAFE_DEREF(structurePtr));

  pushVector("objects", d_objects);
  pushVector("avatars", d_avatars);
}

Sdk::FieldHandled Tile::onFieldNotFound(const std::string& i_name, const Json::Value& i_json)
{
  const auto layer = LayerStr::fromString(i_name);

  auto structurePtr = std::make_shared<Structure>();
  Sdk::JsonSerializer::deserialize(*structurePtr, i_json);

  d_layers[layer] = std::move(structurePtr);

  return true;
}


void Tile::update(const double i_dt)
{
  for (auto& [_, structurePtr] : d_layers)
    SAFE_DEREF(structurePtr).update(i_dt);

  for (auto objPtr : d_objects)
    SAFE_DEREF(objPtr).update(i_dt);

  for (auto avatarPtr : d_avatars)
    SAFE_DEREF(avatarPtr).update(i_dt);
}


const LayersMap& Tile::getLayers() const
{
  return d_layers;
}

const Objects& Tile::getObjects() const
{
  return d_objects;
}

const Avatars& Tile::getAvatars() const
{
  return d_avatars;
}

std::vector<Entity*> Tile::getEntities()
{
  std::vector<Entity*> entities;

  // Add structures and mounts (tile-based entities)
  for (const auto& [_, structurePtr] : d_layers)
  {
    entities.push_back(structurePtr.get());
    if (const auto fixturePtr = SAFE_DEREF(structurePtr).getFixture())
    {
      for (const auto mountPtr : fixturePtr->getMountsFlat())
        entities.push_back(mountPtr);
    }
  }

  // Add objects and avatars (free-based entities)
  for (const auto& objPtr : d_objects)
    entities.push_back(objPtr.get());
  for (const auto& avatarPtr : d_avatars)
    entities.push_back(avatarPtr.get());

  return entities;
}

const std::vector<Entity*> Tile::getEntities() const
{
  return const_cast<Tile*>(this)->getEntities();
}


const StructurePtr Tile::getStructure(Layer i_layer) const
{
  if (d_layers.contains(i_layer))
    return d_layers.at(i_layer);
  return nullptr;
}

void Tile::setStructure(const Layer i_layer, StructurePtr i_structure)
{
  CONTRACT_EXPECT(i_structure);
  CONTRACT_EXPECT(d_layers[i_layer] == nullptr);
  d_layers[i_layer] = i_structure;
}

void Tile::resetStructure(const Layer i_layer)
{
  d_layers.erase(i_layer);
}


void Tile::addObject(ObjectPtr i_object)
{
  CONTRACT_EXPECT(i_object);
  d_objects.push_back(i_object);
}

void Tile::addAvatar(AvatarPtr i_avatar)
{
  CONTRACT_EXPECT(i_avatar);
  d_avatars.push_back(i_avatar);
}

void Tile::removeObject(const Object& i_object)
{
  const int originalSize = (int)d_objects.size();

  d_objects.erase(std::remove_if(d_objects.begin(), d_objects.end(), [&](const auto i_objectPtr) {
    return &i_object == i_objectPtr.get();
    }), d_objects.end());

  const int newSize = (int)d_objects.size();
  CONTRACT_EXPECT(newSize == originalSize - 1);
}

void Tile::removeAvatar(const Avatar& i_avatar)
{
  const int originalSize = (int)d_avatars.size();

  d_avatars.erase(std::remove_if(d_avatars.begin(), d_avatars.end(), [&](const auto i_avatarPtr) {
    return &i_avatar == i_avatarPtr.get();
    }), d_avatars.end());

  const int newSize = (int)d_avatars.size();
  CONTRACT_EXPECT(newSize == originalSize - 1);
}


bool Tile::isSpaceExposed() const
{
  // Any wall always makes the space not exposed
  if (d_layers.find(Layer::Wall) != d_layers.end())
    return false;

  // Floor always makes the space not exposed
  if (d_layers.find(Layer::Floor) != d_layers.end())
    return false;

  // Panneling can expose to space or not
  const auto it = d_layers.find(Layer::Panneling);
  if (it != d_layers.end())
    return SAFE_DEREF(it->second).getStructurePrototype().spaceExposure;

  // If there are no walls, no floors and no panneling, the space is exposed
  return true;
}

bool Tile::isAirTight() const
{
  // Tile can be airtight only if there is a wall structure that is airtight
  const auto it = d_layers.find(Layer::Wall);
  if (it != d_layers.end())
    return SAFE_DEREF(it->second).isAirTight();

  return false;
}


GasThd& Tile::getGasUnitThd()
{
  return d_gasUnitThd;
}

const GasThd& Tile::getGasUnitThd() const
{
  return d_gasUnitThd;
}
