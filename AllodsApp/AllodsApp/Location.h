#pragma once

#include "Fwd.h"
#include "Tile.h"
#include "TileCollection.h"

#include <LaggySdk/EventHandler.h>


class Location : public Sdk::EventHandler
{
public:
  Location();

  void setName(std::string i_name);
  const std::string& getName() const;

  void update(double i_dt);

  // TODO: ae
  // Change to Sdk::Rect2I
  int getMinX() const;
  int getMinY() const;
  int getMaxX() const;
  int getMaxY() const;

  const Tiles& getTiles() const;
  Tile& getOrCreateTile(const TileCoord& i_coord);
  Tile* getTile(const TileCoord& i_coord);
  const Tile* getTile(const TileCoord& i_coord) const;
  
  Objects& getObjects();
  const Objects& getObjects() const;

private:
  std::string d_name;

  int d_minX = 0;
  int d_minY = 0;
  int d_maxX = 0;
  int d_maxY = 0;

  Tiles d_tiles;
  TileCollection d_tileCollection;
  Objects d_objects;
};
