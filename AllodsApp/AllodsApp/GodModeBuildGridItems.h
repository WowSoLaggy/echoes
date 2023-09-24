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
  GodModeBuildGridItem(const StructurePrototype& i_prototype);

  const StructurePrototype& getPrototype() const;

private:
  const StructurePrototype& d_prototype;
};


Dx::GridItems getGodModeBuildGridItems(int i_gridSizeX);
