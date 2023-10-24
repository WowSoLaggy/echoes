#include "stdafx.h"
#include "Location.h"

#include "Avatar.h"
#include "Object.h"

#include <LaggyDx/Simulation.h>

#include <LaggySdk/JsonSerializer.h>
#include <LaggySdk/StringUtils.h>


namespace
{
  const std::string TileTagPreffix = "tile";
  const char TileTagSeparator = '.';

  std::string createTileTag(const TileCoord& i_coord)
  {
    return TileTagPreffix + TileTagSeparator +
      std::to_string(i_coord.x) + TileTagSeparator + std::to_string(i_coord.y);
  }

  bool isTileTag(const std::string& i_tag)
  {
    return i_tag.starts_with(TileTagPreffix + TileTagSeparator);
  }

  TileCoord parseTileCoord(const std::string& i_tag)
  {
    const auto tokens = Sdk::splitString(i_tag, TileTagSeparator);
    CONTRACT_EXPECT(tokens.size() == 3);

    const int x = std::atoi(tokens[1].c_str());
    const int y = std::atoi(tokens[2].c_str());
    return { x, y };
  }

} // anonym NS


Location::Location()
  : d_tileCollection(*this)
{
}


void Location::pushFields()
{
  pushField("name", d_name);

  for (auto& [coord, tile] : d_tiles)
    pushSharedPtr(createTileTag(coord), tile);

  pushVector("objects", d_objects);
  pushVector("avatars", d_avatars);
}

Sdk::FieldHandled Location::onFieldNotFound(const std::string& i_name, const Json::Value& i_json)
{
  if (isTileTag(i_name))
  {
    auto tileCoords = parseTileCoord(i_name);

    auto tile = std::make_shared<Tile>();
    Sdk::JsonSerializer::deserialize(*tile, i_json);

    d_tiles.insert({ std::move(tileCoords), std::move(tile) });
    
    return true;
  }

  return false;
}

void Location::onDeserialized()
{
  updateMinMax();
}


void Location::setName(std::string i_name)
{
  d_name = std::move(i_name);
}

const std::string& Location::getName() const
{
  return d_name;
}


void Location::update(const double i_dt)
{
  Dx::thd::Simulation().update(i_dt, d_tileCollection);

  for (auto& [_, tile] : d_tiles)
    SAFE_DEREF(tile).update(i_dt);

  for (auto objPtr : d_objects)
    SAFE_DEREF(objPtr).update(i_dt);
  for (auto avatarPtr : d_avatars)
    SAFE_DEREF(avatarPtr).update(i_dt);
}


const Sdk::RectI& Location::getRect() const
{
  return d_minMaxRect;
}


const Tiles& Location::getTiles() const
{
  return d_tiles;
}

Tile& Location::getOrCreateTile(const TileCoord& i_coord)
{
  if (auto tile = getTile(i_coord))
    return *tile;

  updateMinMax(i_coord);

  auto tilePtr = std::make_shared<Tile>();
  d_tiles[i_coord] = tilePtr;
  return *tilePtr;
}

TilePtr Location::getTile(const TileCoord& i_coord)
{
  const auto it = d_tiles.find(i_coord);
  return it == d_tiles.end() ? nullptr : it->second;
}

const TilePtr Location::getTile(const TileCoord& i_coord) const
{
  const auto it = d_tiles.find(i_coord);
  return it == d_tiles.end() ? nullptr : it->second;
}


Objects& Location::getObjects()
{
  return d_objects;
}

const Objects& Location::getObjects() const
{
  return d_objects;
}


Avatars& Location::getAvatars()
{
  return d_avatars;
}

const Avatars& Location::getAvatars() const
{
  return d_avatars;
}


void Location::updateMinMax(const TileCoord& i_coord)
{
  if (d_tiles.empty())
  {
    d_minMaxRect.p1 = i_coord;
    d_minMaxRect.p2 = i_coord;
  }
  else
  {
    d_minMaxRect.p1.x = std::min(i_coord.x, d_minMaxRect.p1.x);
    d_minMaxRect.p1.y = std::min(i_coord.y, d_minMaxRect.p1.y);
    d_minMaxRect.p2.x = std::max(i_coord.x, d_minMaxRect.p2.x);
    d_minMaxRect.p2.y = std::max(i_coord.y, d_minMaxRect.p2.y);
  }
}

void Location::updateMinMax()
{
  if (d_tiles.empty())
  {
    d_minMaxRect.p1 = Sdk::Vector2I::zero();
    d_minMaxRect.p2 = Sdk::Vector2I::zero();
    return;
  }

  d_minMaxRect.p1 = d_tiles.begin()->first;
  d_minMaxRect.p2 = d_tiles.begin()->first;

  for (const auto& [coord, _] : d_tiles)
    updateMinMax(coord);
}
