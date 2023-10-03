#pragma once

#include <LaggyDx/ITile.h>


class DummyTileThd : public Dx::thd::ITile
{
public:
  virtual double getT() const override;
  virtual void setT(double i_t) override;
};
