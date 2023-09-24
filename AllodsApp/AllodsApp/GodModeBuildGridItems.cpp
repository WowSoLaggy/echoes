#include "stdafx.h"
#include "GodModeBuildGridItems.h"

#include "PrototypesCollection.h"

#include <LaggyDx/GridItem.h>


namespace
{
  void insertEmptyCells(Dx::GridItems& i_items, const int i_count)
  {
    for (int i = 0; i < i_count; ++i)
      i_items.push_back(nullptr);
  }

} // anonym NS


GodModeBuildGridDestroyItem::GodModeBuildGridDestroyItem()
{
  setTextureName("Destroy.png");
}


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

  // Destroy icon

  items.push_back(std::make_shared<GodModeBuildGridDestroyItem>());
  insertEmptyCells(items, i_gridSizeX - 1);

  // Prototypes per layers

  const auto& prototypes = PrototypesCollection::getStructurePrototypes();

  std::map<Layer, std::vector<std::reference_wrapper<const StructurePrototype>>> layersMap;
  for (const auto& [_, proto] : prototypes)
    layersMap[proto.layer].push_back(std::ref(proto));

  for (const auto& [_, protos] : layersMap)
  {
    for (const auto& proto : protos)
      items.push_back(std::make_shared<GodModeBuildGridItem>(proto));

    const int emptyCells = i_gridSizeX - (protos.size() % i_gridSizeX);
    insertEmptyCells(items, emptyCells);
  }

  return items;
}
