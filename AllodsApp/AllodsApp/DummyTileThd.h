#pragma once

#include <LaggyDx/ITile.h>


class DummyTileThd : public Dx::thd::ITile
{
public:
  virtual std::vector<Dx::thd::IThdObject*> getThdObjectsAll() const override;
  virtual std::vector<Dx::thd::IThdObject*> getThdObjectsExternal() const override;
};
