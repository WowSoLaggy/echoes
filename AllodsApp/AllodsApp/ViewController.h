#pragma once

#include "BackgroundView.h"
#include "Fwd.h"
#include "TileView.h"

#include <LaggyDx/LaggyDxFwd.h>
#include <LaggyDx/ISpriteShader.h>
#include <LaggySdk/EventHandler.h>


class ViewController : public Sdk::EventHandler
{
public:
  ViewController(Game& i_game);
  ~ViewController();

  void update(double i_dt);
  void render();

private:
  std::unique_ptr<Dx::ISpriteShader> d_worldShader;
  const BackgroundView d_backgroundView;
  const TileView d_tileView;
  const Dx::ICamera2* d_camera = nullptr;
  const World* d_world = nullptr;

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void onSessionAttached(Session& i_session);
  void onSessionDetached(Session& i_session);
  void onWorldAdded(World& i_world);
  void onWorldRemoved(World& i_world);

};
