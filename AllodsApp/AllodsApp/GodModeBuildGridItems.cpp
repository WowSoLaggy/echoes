#include "stdafx.h"
#include "GodModeBuildGridItems.h"

#include "PrototypesCollection.h"

#include <LaggyDx/GridItem.h>


GodModeBuildGridItem::GodModeBuildGridItem(const StructurePrototype& i_prototype)
  : d_prototype(i_prototype)
{
}


const StructurePrototype& GodModeBuildGridItem::getPrototype() const
{
  return d_prototype;
}


Dx::GridItems getGodModeBuildGridItems()
{
  Dx::GridItems items;

  const auto& prototypes = PrototypesCollection::getStructurePrototypes();
  for (const auto& [_, proto] : prototypes)
  {
    auto item = std::make_shared<GodModeBuildGridItem>(proto);
    item->setTextureName(proto.textureName);
    items.push_back(std::move(item));
  }

  return items;
}
