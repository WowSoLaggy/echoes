#pragma once

#include "Fwd.h"

#include <LaggyDx/ITileCollection.h>


class TileCollection : public Dx::thd::ITileCollection
{
public:
  TileCollection(Location& i_location);

  virtual int minX() const override;
  virtual int minY() const override;
  virtual int maxX() const override;
  virtual int maxY() const override;

  virtual std::shared_ptr<Dx::thd::ITile> getTile(const Sdk::Vector2I& i_coords) const override;

private:
  Location& d_location;
};
