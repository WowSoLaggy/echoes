#pragma once

#include "Fwd.h"

#include <LaggyDx/ITile.h>


class TileThd : public Dx::thd::ITile
{
public:
  TileThd(Tile& i_tile);

  virtual double getT() const override;
  virtual void setT(double i_t) override;

  virtual Dx::thd::VolumeUnit& getVolumeUnit() override;
  virtual const Dx::thd::VolumeUnit& getVolumeUnit() const override;

private:
  Tile& d_tile;
};
