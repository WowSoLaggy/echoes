#pragma once

#include "BackgroundView.h"
#include "BuildModeView.h"
#include "Fwd.h"
#include "TileView.h"

#include <LaggyDx/ISpriteShader.h>
#include <LaggyDx/LaggyDxFwd.h>
#include <LaggySdk/EventHandler.h>


class ViewController : public Sdk::EventHandler
{
public:
  ViewController(Game& i_game);
  ~ViewController();

  void update(double i_dt);
  void render();

private:
  std::unique_ptr<Dx::ISpriteShader> d_locationShader;

  const BackgroundView d_backgroundView;
  const TileView d_tileView;
  BuildModeView d_buildModeView;

  const Dx::ICamera2* d_camera = nullptr;
  const Location* d_location = nullptr;

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void onSessionAttached(Session& i_session);
  void onSessionDetached(Session& i_session);
  void onLocationAdded(Location& i_location);
  void onLocationRemoved(Location& i_location);
  void OnBuildDraftSet(std::shared_ptr<BuildDraftInfo> i_buildDraftInfo);
};
