#pragma once

#include <LaggyDx/ITile.h>


class DummyTileThd : public Dx::thd::ITile
{
public:
  virtual double getT() const override;
  virtual void setT(double i_t) override;

  virtual const Dx::thd::VolumeUnit& getVolumeUnit() const override;
  virtual void setVolumeUnit(Dx::thd::VolumeUnit i_volumeUnit) override;
};
