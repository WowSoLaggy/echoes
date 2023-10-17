#pragma once

#include "Fwd.h"

#include <LaggyDx/ITileCollection.h>


class TileCollection : public Dx::thd::ITileCollection
{
public:
  TileCollection(Location& i_location);

  virtual const Sdk::RectI& getRect() const override;

  virtual std::shared_ptr<Dx::thd::ITile> getTile(const Sdk::Vector2I& i_coords) const override;

private:
  Location& d_location;
};
