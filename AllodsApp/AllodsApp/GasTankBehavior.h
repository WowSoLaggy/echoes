#pragma once

#include "IBehaviorModel.h"

#include <LaggyDx/VolumeUnit.h>


class GasTankBehavior : public IBehaviorModel
{
public:
  GasTankBehavior();
  GasTankBehavior(Entity& i_gasTank);

  virtual void pushFields() override;
  virtual void interact() override;

  virtual BehaviorModel getModelType() const override;

  void setGasTank(Entity& i_gasTank);

  void open();
  void close();
  void switchState();

  bool isOpen() const;
  bool isClose() const;

private:

  enum class State : std::int32_t
  {
    Open = 0,
    Close,
  };

  Entity* d_gasTank = nullptr;
  State d_state = State::Open;

  Entity& getGasTank() const;

  Dx::thd::VolumeUnit d_volumeUnit;
};
