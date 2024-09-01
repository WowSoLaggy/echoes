#pragma once

#include "Fwd.h"

#include <LaggyDx/ITile.h>


class TileThd : public Dx::thd::ITile
{
public:
  TileThd(Tile& i_tile);

  virtual std::optional<double> getTemperature() const override;
  virtual void setTemperature(double i_t) override;
  virtual double getThermalConductivity() const override;
  virtual double getHeatCapacity() const override;

  virtual bool isAirTight() const override;

  virtual Dx::thd::Unit& getUnit() override;
  virtual const Dx::thd::Unit& getUnit() const override;

  virtual std::vector<Dx::thd::IThdObject*> getHeatAgents() const override;

  virtual void afterUpdate(double i_dt) override;

private:
  Tile& d_tile;

  void leakGasesToSpace(double i_dt);
};
