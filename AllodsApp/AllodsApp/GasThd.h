#pragma once

#include <LaggyDx/GasUnit.h>
#include <LaggyDx/IThdObject.h>


class GasThd : public Dx::thd::IThdObject
{
public:
  virtual void setTemperature(double i_temperature) override;
  [[nodiscard]] virtual double getTemperature() const override;
  [[nodiscard]] virtual double getThermalConductivity() const override;
  [[nodiscard]] virtual double getHeatCapacity() const override;

  [[nodiscard]] virtual Dx::thd::GasUnit* getGasUnit();
  [[nodiscard]] virtual const Dx::thd::GasUnit* getGasUnit() const;

private:
  Dx::thd::GasUnit d_gasUnit;
  double d_temperature = 0;
};
