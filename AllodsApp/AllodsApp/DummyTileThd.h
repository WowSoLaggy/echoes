#pragma once

#include <LaggyDx/ITile.h>


class DummyTileThd : public Dx::thd::ITile
{
public:
  virtual std::optional<double> getTemperature() const override;
  virtual void setTemperature(double i_t) override;
  virtual double getThermalConductivity() const override;
  virtual double getHeatCapacity() const override;

  virtual bool isAirTight() const override;

  virtual Dx::thd::Unit& getUnit() override;
  virtual const Dx::thd::Unit& getUnit() const override;

  virtual std::vector<Dx::thd::IThdObject*> getHeatAgents() const override;

};
