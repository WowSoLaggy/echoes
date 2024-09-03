#pragma once

#include <LaggyDx/ITile.h>


class DummyTileThd : public Dx::thd::ITile
{
public:
  virtual std::vector<Dx::thd::IThdObject*> getThdObjects() const override;
};
