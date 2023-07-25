#pragma once

#include "Terrain.h"

#include <LaggySdk/EventHandler.h>


class World : public Sdk::EventHandler
{
public:
  void setTerrain(std::unique_ptr<Terrain> i_terrain);
  Terrain* getTerrain() const;

private:
  std::unique_ptr<Terrain> d_terrain;
};
