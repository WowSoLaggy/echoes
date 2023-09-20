#include "stdafx.h"
#include "GodModeBuildGridItems.h"

#include "PrototypesCollection.h"

#include <LaggyDx/GridItem.h>


Dx::GridItems getGodModeBuildGridItems()
{
  Dx::GridItems items;

  const auto& prototypes = PrototypesCollection::getStructurePrototypes();
  for (const auto& [_, proto] : prototypes)
  {
    auto item = std::make_shared<Dx::GridItem>();
    item->setTextureName(proto.textureName);
    items.push_back(std::move(item));
  }

  return items;
}
