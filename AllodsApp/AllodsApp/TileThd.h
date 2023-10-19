#pragma once

#include "Fwd.h"

#include <LaggyDx/ITile.h>


class TileThd : public Dx::thd::ITile
{
public:
  TileThd(Tile& i_tile);

  virtual double getT() const override;
  virtual void setT(double i_t) override;

  virtual const Dx::thd::VolumeUnit& getVolumeUnit() const override;
  virtual void setVolumeUnit(Dx::thd::VolumeUnit i_volumeUnit) override;

private:
  Tile& d_tile;
};
