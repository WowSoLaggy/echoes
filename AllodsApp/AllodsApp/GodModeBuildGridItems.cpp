#include "stdafx.h"
#include "GodModeBuildGridItems.h"

#include "PrototypesCollection.h"

#include <LaggyDx/GridItem.h>
#include <LaggyDx/TextureUtils.h>


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
  setTexture(&Dx::TextureUtils::getTexture("Destroy.png"));
}


GodModeBuildGridItem::GodModeBuildGridItem(const Prototype& i_prototype)
  : d_prototype(i_prototype)
{
  setTexture(i_prototype.texture);
}


const Prototype& GodModeBuildGridItem::getPrototype() const
{
  return d_prototype;
}


Dx::GridItems getGodModeBuildGridItems(const int i_gridSizeX)
{
  Dx::GridItems items;

  // Destroy icon

  items.push_back(std::make_shared<GodModeBuildGridDestroyItem>());
  insertEmptyCells(items, i_gridSizeX - 1);

  // Structure prototypes per layers

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

  // Mounts

  const auto& mounts = PrototypesCollection::getMountPrototypes();
  for (const auto& [_, proto] : mounts)
  {
    items.push_back(std::make_shared<GodModeBuildGridItem>(proto));
    const int emptyCells = i_gridSizeX - (mounts.size() % i_gridSizeX);
    insertEmptyCells(items, emptyCells);
  }

  return items;
}
