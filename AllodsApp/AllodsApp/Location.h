#pragma once

#include "Tile.h"

#include <LaggySdk/EventHandler.h>


class Location : public Sdk::EventHandler
{
public:
  void setName(std::string i_name);
  const std::string& getName() const;

  void update(double i_dt);

  const Tiles& getTiles() const;
  Tile& getOrCreateTile(const TileCoord& i_coord);
  Tile* getTile(const TileCoord& i_coord);
  const Tile* getTile(const TileCoord& i_coord) const;

private:
  std::string d_name;
  Tiles d_tiles;
};
