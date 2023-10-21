#include "stdafx.h"
#include "DevBuildGridItems.h"

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


DevBuildGridDestroyItem::DevBuildGridDestroyItem()
{
  setTexture(&Dx::TextureUtils::getTexture("Destroy.png"));
}


DevBuildGridItem::DevBuildGridItem(PrototypePtr i_prototype)
  : d_prototype(i_prototype)
{
  setTexture(SAFE_DEREF(i_prototype).texture);
}


PrototypePtr DevBuildGridItem::getPrototype() const
{
  return d_prototype;
}


Dx::GridItems getDevBuildGridItems(const int i_gridSizeX)
{
  Dx::GridItems items;

  // Destroy icon

  items.push_back(std::make_shared<DevBuildGridDestroyItem>());
  insertEmptyCells(items, i_gridSizeX - 1);

  // Structure prototypes per layers

  const auto& prototypes = PrototypesCollection::getStructurePrototypes();

  std::map<Layer, std::vector<PrototypePtr>> layersMap;
  for (const auto& [_, proto] : prototypes)
  {
    const auto& structurePrototype = SAFE_DEREF(dynamic_cast<const StructurePrototype*>(proto.get()));
    layersMap[structurePrototype.layer].push_back(proto);
  }

  for (const auto& [_, protos] : layersMap)
  {
    for (const auto& proto : protos)
      items.push_back(std::make_shared<DevBuildGridItem>(proto));

    const int emptyCellsAfterLayer = i_gridSizeX - (protos.size() % i_gridSizeX);
    insertEmptyCells(items, emptyCellsAfterLayer);
  }

  // Mounts

  const auto& mounts = PrototypesCollection::getMountPrototypes();
  for (const auto& [_, proto] : mounts)
    items.push_back(std::make_shared<DevBuildGridItem>(proto));
  const int emptyCellsAfterMounts = i_gridSizeX - (mounts.size() % i_gridSizeX);
  insertEmptyCells(items, emptyCellsAfterMounts);

  // Objects

  const auto& objects = PrototypesCollection::getObjectPrototypes();
  for (const auto& [_, proto] : objects)
    items.push_back(std::make_shared<DevBuildGridItem>(proto));
  const int emptyCellsAfterObjects = i_gridSizeX - (objects.size() % i_gridSizeX);
  insertEmptyCells(items, emptyCellsAfterObjects);

  return items;
}
