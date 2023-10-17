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
  GodModeBuildGridItem(PrototypePtr i_prototype);

  PrototypePtr getPrototype() const;

private:
  PrototypePtr d_prototype;
};


Dx::GridItems getGodModeBuildGridItems(int i_gridSizeX);
