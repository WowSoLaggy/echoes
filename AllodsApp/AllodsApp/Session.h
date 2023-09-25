#pragma once

#include "BuildManager.h"
#include "InteractionManager.h"
#include "Location.h"

#include <LaggyDx/ICamera2.h>
#include <LaggyDx/IInputController.h>
#include <LaggyDx/MouseKeys.h>
#include <LaggySdk/EventHandler.h>


class Session : public Sdk::EventHandler
{
public:
  Session();

  void update(double i_dt);
  void onMouseMove();
  bool onMouseClick(Dx::MouseKey i_key);
  void onMouseRelease(Dx::MouseKey i_key);

  void setCurrentLocation(std::unique_ptr<Location> i_location);
  Location* getCurrentLocation() const;

  BuildManager& getBuildManger();

  Dx::ICamera2& getCamera() const;

  void onEscape();
  void pause(bool i_silent = false);
  void unpause(bool i_silent = false);

  void enableGodMode(bool i_silent = false);
  void disableGodMode(bool i_silent = false);
  bool isGodMode() const;

private:
  std::unique_ptr<Dx::ICamera2> d_camera;
  std::unique_ptr<Dx::IInputController> d_inputController;
  std::unique_ptr<Location> d_currentLocation;

  bool d_pause = false;
  bool d_godMode = true;

  BuildManager d_buildManager;
  InteractionManager d_interactionManager;

  void attachFreeCameraController();
  void detachFreeCameraController();
};
