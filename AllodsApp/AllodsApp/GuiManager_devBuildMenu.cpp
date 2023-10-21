#include "stdafx.h"
#include "GuiManager.h"

#include "Game.h"
#include "GodModeBuildGridItems.h"
#include "GuiCreator.h"
#include "Session.h"

#include <LaggyDx/Grid.h>


void GuiManager::onGodModeBuildSelectedItem(const Dx::GridItem& i_item)
{
  CONTRACT_EXPECT(d_session);

  if (const auto* item = dynamic_cast<const GodModeBuildGridItem*>(&i_item))
    d_session->getBuildManger().setBuildDraft(item->getPrototype());
  else if (const auto* item = dynamic_cast<const GodModeBuildGridDestroyItem*>(&i_item))
    d_session->getBuildManger().startRemovalMode();
}

void GuiManager::onGodModeBuildUnselectedItem()
{
  CONTRACT_EXPECT(d_session);
  d_session->getBuildManger().resetBuildDraft();
  d_session->getBuildManger().stopRemovalMode();
}

bool GuiManager::isGodModeBuildMenuShown() const
{
  return d_godModeBuildGrid;
}

void GuiManager::showGodModeBuildMenu()
{
  CONTRACT_EXPECT(!d_godModeBuildGrid);

  constexpr int GridSizeX = 3;
  auto items = getGodModeBuildGridItems(GridSizeX);

  const int gridSizeY = ((int)items.size() - 1) / GridSizeX + 1;

  d_godModeBuildGrid = &GuiCreator::createGrid(d_game.getForm(), GridSizeX, gridSizeY);
  d_godModeBuildGrid->setItems(std::move(items));
  d_godModeBuildGrid->setPosition({ 16, 16 });
  d_godModeBuildGrid->setSelectionEnabled(true);

  d_godModeBuildGrid->setOnItemSelected(
    std::bind(&GuiManager::onGodModeBuildSelectedItem, this, std::placeholders::_1));
  d_godModeBuildGrid->setOnItemUnselected(std::bind(&GuiManager::onGodModeBuildUnselectedItem, this));
}

void GuiManager::hideGodModeBuildMenu()
{
  if (d_godModeBuildGrid)
  {
    d_godModeBuildGrid->setParent(nullptr);
    d_godModeBuildGrid = nullptr;
  }

  CONTRACT_EXPECT(d_session);
  d_session->getBuildManger().resetBuildDraft();
  d_session->getBuildManger().stopRemovalMode();
}

void GuiManager::onExitBuildRemoval()
{
  if (d_godModeBuildGrid)
    d_godModeBuildGrid->unselectItem();
}
