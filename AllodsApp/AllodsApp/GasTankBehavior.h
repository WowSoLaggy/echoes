#pragma once

#include "Gases.h"
#include "IBehaviorModel.h"

#include <LaggyDx/VolumeUnit.h>


class GasTankBehavior : public IBehaviorModel
{
public:
  enum class State : std::int32_t
  {
    Open = 0,
    Closed,
  };
  DECLARE_ENUM_STR(State);

public:
  GasTankBehavior();
  GasTankBehavior(Entity& i_gasTank);

  virtual void pushFields() override;

  virtual void update(double i_dt) override;

  virtual void interact() override;

  virtual BehaviorModel getModelType() const override;
  virtual std::string getDescription() const override;
  virtual BehaviorActions getActions(bool i_devMode) override;

  void setGasTank(Entity& i_gasTank);

  void open();
  void close();
  void switchState();

  bool isOpen() const;
  bool isClose() const;

private:
  Entity* d_gasTank = nullptr;
  State d_state = State::Closed;

  Entity& getGasTank() const;

  Dx::thd::VolumeUnit d_volumeUnit;

  std::unordered_map<Gas, double> getGasesRatio() const;
};
