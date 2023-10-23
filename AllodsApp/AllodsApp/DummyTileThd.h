#pragma once

#include <LaggyDx/ITile.h>


class DummyTileThd : public Dx::thd::ITile
{
public:
  virtual double getT() const override;
  virtual void setT(double i_t) override;

  virtual Dx::thd::VolumeUnit& getVolumeUnit() override;
  virtual const Dx::thd::VolumeUnit& getVolumeUnit() const override;
};
