#pragma once

#include "Fwd.h"

#include <LaggyDx/ITile.h>


class TileThd : public Dx::thd::ITile
{
public:
  TileThd(Tile& i_tile);

  virtual double getT() const override;
  virtual void setT(double i_t) override;

  virtual double getInsulationFactor() const override;
  virtual bool isAirTight() const override;

  virtual Dx::thd::Unit& getUnit() override;
  virtual const Dx::thd::Unit& getUnit() const override;

private:
  Tile& d_tile;
};
