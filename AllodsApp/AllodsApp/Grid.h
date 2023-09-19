#pragma once

#include <LaggyDx/Control.h>
#include <LaggyDx/Sprite.h>


class Grid : public Dx::Control
{
public:
  Grid(int i_slotsX, int i_slotsY);

  virtual void render(Dx::IRenderer2d& i_renderer) const override;

  void resize(int i_slotsX, int i_slotsY);

private:
  int d_slotsX = 0;
  int d_slotsY = 0;

  std::vector<Dx::Sprite> d_gridSprites;
  std::vector<Dx::Sprite> d_slotSprites;

  void createGridSprites();
};
