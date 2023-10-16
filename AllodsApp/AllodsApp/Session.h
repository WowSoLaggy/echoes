#pragma once

#include "BuildManager.h"
#include "InteractionManager.h"
#include "IOverlay.h"
#include "Location.h"
#include "OverlayTypes.h"
#include "World.h"

#include <LaggyDx/ICamera2.h>
#include <LaggyDx/IInputController.h>
#include <LaggyDx/MouseKeys.h>

#include <LaggySdk/EventHandler.h>
#include <LaggySdk/ISerializable.h>


class Session : public Sdk::EventHandler, public Sdk::ISerializable
{
public:
  Session();

  virtual void pushFields() override;

  void update(double i_dt);
  void onMouseMove();
  bool onMouseClick(Dx::MouseKey i_key);
  void onMouseRelease(Dx::MouseKey i_key);

  void setScenario(std::shared_ptr<Scenario> i_scenario);
  const Scenario* getScenario() const;

  void setWorld(std::shared_ptr<World> i_world);
  World* getWorld() const;

  void setCurrentLocation(Location* i_location);
  Location* getCurrentLocation() const;

  BuildManager& getBuildManger();

  Dx::ICamera2& getCamera() const;

  void onEscape();
  void pause(bool i_silent = false);
  void unpause(bool i_silent = false);
  bool isPause() const;

  void enableGodMode();
  void disableGodMode();
  bool isGodMode() const;

  const IOverlay* getOverlay() const;
  void setOverlay(OverlayType i_overlayType);
  void resetOverlay();

private:
  std::shared_ptr<Scenario> d_scenario;

  std::shared_ptr<Dx::ICamera2> d_camera;
  std::shared_ptr<Dx::IInputController> d_inputController;
  std::shared_ptr<World> d_world;
  Location* d_currentLocation = nullptr;
  
  bool d_pause = false;
  bool d_godMode = true;

  BuildManager d_buildManager;
  InteractionManager d_interactionManager;

  std::unique_ptr<IOverlay> d_overlay;

  void attachFreeCameraController();
  void detachFreeCameraController();
};
