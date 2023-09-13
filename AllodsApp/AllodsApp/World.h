#pragma once

#include "Tile.h"

#include <LaggySdk/EventHandler.h>


class World : public Sdk::EventHandler
{
public:
  void update(double i_dt);

  const Tiles& getTiles() const;
  Tile& getOrCreateTile(const TileCoord& i_coord);

private:
  Tiles d_tiles;
};
