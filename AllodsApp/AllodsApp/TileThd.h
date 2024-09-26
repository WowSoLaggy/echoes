#pragma once

#include "Fwd.h"

#include <LaggyDx/ITile.h>


class TileThd : public Dx::thd::ITile
{
public:
  explicit TileThd(Tile& i_tile);

  virtual std::vector<Dx::thd::IThdObject*> getThdObjectsAll() const override;
  virtual std::vector<Dx::thd::IThdObject*> getThdObjectsExternal() const override;

private:
  Tile& d_tile;
};
