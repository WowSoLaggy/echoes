#pragma once

#include "World.h"

#include <LaggyDx/ICamera2.h>
#include <LaggySdk/EventHandler.h>


class Session : public Sdk::EventHandler
{
public:
  Session();

  void setWorld(std::unique_ptr<World> i_world);
  World* getWorld() const;

  Dx::ICamera2& getCamera() const;

private:
  std::unique_ptr<Dx::ICamera2> d_camera;
  std::unique_ptr<World> d_world;
};
