#pragma once

#include "World.h"

#include <LaggySdk/EventHandler.h>


class Session : public Sdk::EventHandler
{
public:
  void setWorld(std::unique_ptr<World> i_world);
  World* getWorld() const;

private:
  std::unique_ptr<World> d_world;
};
