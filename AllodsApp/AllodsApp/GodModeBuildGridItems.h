#pragma once

#include "Fwd.h"

#include <LaggyDx/GridItem.h>
#include <LaggyDx/LaggyDxFwd.h>


class GodModeBuildGridDestroyItem : public Dx::GridItem
{
public:
  GodModeBuildGridDestroyItem();
};


class GodModeBuildGridItem : public Dx::GridItem
{
public:
  GodModeBuildGridItem(const Prototype& i_prototype);

  const Prototype& getPrototype() const;

private:
  const Prototype& d_prototype;
};


Dx::GridItems getGodModeBuildGridItems(int i_gridSizeX);
