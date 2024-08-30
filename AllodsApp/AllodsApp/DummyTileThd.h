#pragma once

#include <LaggyDx/ITile.h>


class DummyTileThd : public Dx::thd::ITile
{
public:
  virtual std::optional<double> getT() const override;
  virtual void setT(double i_t) override;

  virtual double getInsulationFactor() const override;
  virtual bool isAirTight() const override;

  virtual Dx::thd::Unit& getUnit() override;
  virtual const Dx::thd::Unit& getUnit() const override;
};
