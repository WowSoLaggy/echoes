#pragma once

#include "BuildManager.h"
#include "World.h"

#include <LaggyDx/ICamera2.h>
#include <LaggyDx/IInputController.h>
#include <LaggySdk/EventHandler.h>


class Session : public Sdk::EventHandler
{
public:
  Session();

  void update();
  void onMouseMove();

  void setWorld(std::unique_ptr<World> i_world);
  World* getWorld() const;

  BuildManager& getBuildManger();

  Dx::ICamera2& getCamera() const;

  void enableGodMode(bool i_silent = false);
  void disableGodMode(bool i_silent = false);
  bool isGodMode() const;

private:
  std::unique_ptr<Dx::ICamera2> d_camera;
  std::unique_ptr<Dx::IInputController> d_inputController;
  std::unique_ptr<World> d_world;

  bool d_godMode = true;

  BuildManager d_buildManager;
};
