#pragma once

#include "Fwd.h"
#include "TerrainView.h"

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

  std::unique_ptr<TerrainView> d_terrainView;

  virtual void processEvent(const Sdk::IEvent& i_event) override;

  void onSessionAttached(Session& i_session);
  void onSessionDetached(Session& i_session);
  void onWorldAdded(World& i_world);
  void onWorldRemoved(World& i_world);
  void onTerrainAdded(const Terrain& i_terrain);
  void onTerrainRemoved();

};
