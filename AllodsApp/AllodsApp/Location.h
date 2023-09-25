#pragma once

#include "Tile.h"

#include <LaggySdk/EventHandler.h>


class Location : public Sdk::EventHandler
{
public:
  void update(double i_dt);

  const Tiles& getTiles() const;
  Tile& getOrCreateTile(const TileCoord& i_coord);
  Tile* getTile(const TileCoord& i_coord);
  const Tile* getTile(const TileCoord& i_coord) const;

private:
  Tiles d_tiles;
};
