#include "stdafx.h"
#include "GodModeBuildGridItems.h"

#include "PrototypesCollection.h"

#include <LaggyDx/GridItem.h>


GodModeBuildGridItem::GodModeBuildGridItem(const StructurePrototype& i_prototype)
  : d_prototype(i_prototype)
{
  setTextureName(i_prototype.textureName);
}


const StructurePrototype& GodModeBuildGridItem::getPrototype() const
{
  return d_prototype;
}


Dx::GridItems getGodModeBuildGridItems(const int i_gridSizeX)
{
  Dx::GridItems items;

  const auto& prototypes = PrototypesCollection::getStructurePrototypes();

  std::map<Layer, std::vector<std::reference_wrapper<const StructurePrototype>>> layersMap;
  for (const auto& [_, proto] : prototypes)
    layersMap[proto.layer].push_back(std::ref(proto));

  for (const auto& [_, protos] : layersMap)
  {
    for (const auto& proto : protos)
      items.push_back(std::make_shared<GodModeBuildGridItem>(proto));

    const int emptyCells = i_gridSizeX - (protos.size() % i_gridSizeX);
    for (int i = 0; i < emptyCells; ++i)
      items.push_back(nullptr);
  }

  return items;
}
