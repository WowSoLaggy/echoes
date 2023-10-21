#include "stdafx.h"
#include "GuiManager.h"

#include "Game.h"
#include "DevBuildGridItems.h"
#include "GuiCreator.h"
#include "Session.h"

#include <LaggyDx/Grid.h>


void GuiManager::onDevBuildSelectedItem(const Dx::GridItem& i_item)
{
  CONTRACT_EXPECT(d_session);

  if (const auto* item = dynamic_cast<const DevBuildGridItem*>(&i_item))
    d_session->getBuildManger().setBuildDraft(item->getPrototype());
  else if (const auto* item = dynamic_cast<const DevBuildGridDestroyItem*>(&i_item))
    d_session->getBuildManger().startRemovalMode();
}

void GuiManager::onDevBuildUnselectedItem()
{
  CONTRACT_EXPECT(d_session);
  d_session->getBuildManger().resetBuildDraft();
  d_session->getBuildManger().stopRemovalMode();
}

bool GuiManager::isDevBuildMenuShown() const
{
  return d_devBuildGrid;
}

void GuiManager::showDevBuildMenu()
{
  CONTRACT_EXPECT(!d_devBuildGrid);

  constexpr int GridSizeX = 3;
  auto items = getDevBuildGridItems(GridSizeX);

  const int gridSizeY = ((int)items.size() - 1) / GridSizeX + 1;

  d_devBuildGrid = &GuiCreator::createGrid(d_game.getForm(), GridSizeX, gridSizeY);
  d_devBuildGrid->setItems(std::move(items));
  d_devBuildGrid->setPosition({ 16, 16 });
  d_devBuildGrid->setSelectionEnabled(true);

  d_devBuildGrid->setOnItemSelected(
    std::bind(&GuiManager::onDevBuildSelectedItem, this, std::placeholders::_1));
  d_devBuildGrid->setOnItemUnselected(std::bind(&GuiManager::onDevBuildUnselectedItem, this));
}

void GuiManager::hideDevBuildMenu()
{
  if (d_devBuildGrid)
  {
    d_devBuildGrid->setParent(nullptr);
    d_devBuildGrid = nullptr;
  }

  CONTRACT_EXPECT(d_session);
  d_session->getBuildManger().resetBuildDraft();
  d_session->getBuildManger().stopRemovalMode();
}

void GuiManager::onExitBuildRemoval()
{
  if (d_devBuildGrid)
    d_devBuildGrid->unselectItem();
}
