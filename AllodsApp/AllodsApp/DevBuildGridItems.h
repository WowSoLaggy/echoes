#pragma once

#include "Fwd.h"

#include <LaggyDx/GridItem.h>
#include <LaggyDx/LaggyDxFwd.h>


class DevBuildGridDestroyItem : public Dx::GridItem
{
public:
  DevBuildGridDestroyItem();
};


class DevBuildGridItem : public Dx::GridItem
{
public:
  DevBuildGridItem(PrototypePtr i_prototype);

  PrototypePtr getPrototype() const;

private:
  PrototypePtr d_prototype;
};


Dx::GridItems getDevBuildGridItems(int i_gridSizeX);
