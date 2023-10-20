#include "stdafx.h"
#include "GuiManager.h"

#include "CtxMenuContent.h"
#include "Fonts.h"
#include "Game.h"
#include "GameEvents.h"
#include "GuiCreator.h"
#include "GodModeBuildGridItems.h"
#include "InteractionManagerEvents.h"
#include "IOverlay.h"
#include "Location.h"
#include "Session.h"
#include "SessionEvents.h"
#include "TileUtils.h"

#include <LaggyDx/App.h>
#include <LaggyDx/Button.h>
#include <LaggyDx/Colors.h>
#include <LaggyDx/CursorUtils.h>
#include <LaggyDx/Grid.h>
#include <LaggyDx/GridItem.h>
#include <LaggyDx/IFontResource.h>
#include <LaggyDx/IResourceController.h>
#include <LaggyDx/Label.h>
#include <LaggyDx/Layout.h>
#include <LaggyDx/Panel.h>
#include <LaggyDx/TextureUtils.h>

#include <LaggySdk/StringUtils.h>


namespace
{
  const Sdk::Vector2I& getResolution()
  {
    const auto& rd = Dx::App::get().getRenderDevice();
    return rd.getResolution();
  }

  std::string getOverlayName(const OverlayType i_type)
  {
    switch (i_type)
    {
    case OverlayType::Temp:
      return "Temperature";
    case OverlayType::Atmo:
      return "Gases";

    default:
      CONTRACT_EXPECT(false);
    }
  }

} // anonym NS


GuiManager::GuiManager(Game& i_game)
  : d_game(i_game)
{
  connectTo(d_game);
}


void GuiManager::processEvent(const Sdk::IEvent& i_event)
{
  if (const auto* event = dynamic_cast<const GameStateChangedEvent*>(&i_event))
    onGameStateChanged(event->getNewState());

  else if (const auto* event = dynamic_cast<const SessionAttachedEvent*>(&i_event))
    onSessionAttached(event->getSession());
  else if (const auto* event = dynamic_cast<const SessionDetachedEvent*>(&i_event))
    onSessionDetached(event->getSession());
  
  else if (const auto* event = dynamic_cast<const GodModeEvent*>(&i_event))
    onGodModeEvent(event->getEnabled());
  
  else if (const auto* event = dynamic_cast<const PauseEvent*>(&i_event))
    showPauseMenu();
  else if (const auto* event = dynamic_cast<const UnpauseEvent*>(&i_event))
    hidePauseMenu();
  
  else if (const auto* event = dynamic_cast<const ExitBuildRemovalEvent*>(&i_event))
    onExitBuildRemoval();
  
  else if (const auto* event = dynamic_cast<const OverlaySetEvent*>(&i_event))
    onOverlaySet(event->getOverlay());

  else if (const auto* event = dynamic_cast<const ShowCtxMenuEvent*>(&i_event))
    showCtxMenu(event->getCtxMenuContent());
  else if (const auto* event = dynamic_cast<const HideCtxMenuEvent*>(&i_event))
    hideCtxMenu();
}


void GuiManager::update()
{
  if (!d_session || d_session->isPause())
    return;

  if (d_overlayHint)
    updateOverlayHint();
}


void GuiManager::onSessionAttached(Session& i_session)
{
  CONTRACT_ASSERT(!d_session);

  d_session = &i_session;
  connectTo(i_session);
  connectTo(i_session.getInteractionManger());
  
  hideMainMenu();
  showInGameGui();
}

void GuiManager::onSessionDetached(Session& i_session)
{
  hideInGameGui();

  disconnectFrom(i_session);
  d_session = nullptr;

  showMainMenu();
}

void GuiManager::showPauseMenu()
{
  CONTRACT_EXPECT(!d_pauseMenuPanel);

  d_pauseMenuPanel = &GuiCreator::createPanel(d_game.getForm());
  d_pauseMenuPanel->sendToFront();
  d_pauseMenuPanel->setTexture(Dx::TextureUtils::getTexture("Black.png"));
  d_pauseMenuPanel->setSize(getResolution().getVector<float>());
  d_pauseMenuPanel->setColor(Dx::colorWithAlpha(Dx::Colors::White, 0.5f));

  auto& layout = GuiCreator::createLayout(*d_pauseMenuPanel);
  layout.setSize(d_pauseMenuPanel->getSize());
  layout.setAlign(Dx::LayoutAlign::TopToBottom_Center);

  const auto createFakePanel = [&]()
  {
    auto& fakePanel = GuiCreator::createPanel(layout);
    fakePanel.setSize({ 0, 16 });
  };

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Resume Game");
    btn.setOnPress(std::bind(&GuiManager::onResumeGame, this));
  }

  createFakePanel();

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Save Game");
    btn.setOnPress(std::bind(&Game::saveSession, &d_game));
  }

  createFakePanel();

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Exit to Menu");
    btn.setOnPress(std::bind(&GuiManager::onExitToMenu, this));
  }

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Exit to Desktop");
    btn.setOnPress(std::bind(&Game::closeApplication, &d_game));
  }
}

void GuiManager::hidePauseMenu()
{
  CONTRACT_EXPECT(d_pauseMenuPanel);
  d_pauseMenuPanel->setParent(nullptr);
  d_pauseMenuPanel = nullptr;
}


void GuiManager::onGodModeEvent(bool i_enabled)
{
  i_enabled ? onGodModeOn() : onGodModeOff();
}

void GuiManager::onGodModeOn()
{
  recreateInGameMenu();
}

void GuiManager::onGodModeOff()
{
  recreateInGameMenu();
  hideGodModeBuildMenu();
}


void GuiManager::onBtnGodMode()
{
  CONTRACT_EXPECT(d_session);
  d_session->enableGodMode();
}

void GuiManager::onBtnLiveMode()
{
  CONTRACT_EXPECT(d_session);
  d_session->disableGodMode();
}


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


void GuiManager::onGameStateChanged(const GameState i_newState)
{
  if (i_newState == GameState::Loading)
    showLoadingScreen();
  else if (i_newState == GameState::Loaded)
  {
    hideLoadingScreen();
    showMainMenu();
  }
}


void GuiManager::showLoadingScreen()
{
  auto& background = GuiCreator::createPanel(d_game.getForm());
  background.setTexture(Dx::TextureUtils::getTexture("Black.png"));
  background.setSize(getResolution().getVector<float>());

  auto& layout = GuiCreator::createLayout(d_game.getForm());
  layout.setSize(getResolution().getVector<float>());
  layout.setAlign(Dx::LayoutAlign::TopToBottom_Center);

  auto& loadingLabel = GuiCreator::createLabel(layout);
  loadingLabel.setText("Loading...");
}

void GuiManager::hideLoadingScreen()
{
  d_game.getForm().removeChildren();
}


void GuiManager::showMainMenu()
{
  auto& background = GuiCreator::createPanel(d_game.getForm());
  background.setTexture(Dx::TextureUtils::getTexture("Black.png"));
  background.setSize(getResolution().getVector<float>());

  auto& layout = GuiCreator::createLayout(d_game.getForm());
  layout.setSize(getResolution().getVector<float>());
  layout.setAlign(Dx::LayoutAlign::TopToBottom_Center);

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Start New Game");
    btn.setOnPress(std::bind(&Game::newSession, &d_game));
  }

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Load Game");
    btn.setOnPress(std::bind(&Game::loadSession, &d_game));
  }

  {
    auto& btn = GuiCreator::createMenuButton(layout);
    btn.setText("Exit to Desktop");
    btn.setOnPress(std::bind(&Game::closeApplication, &d_game));
  }
}

void GuiManager::hideMainMenu()
{
  d_game.getForm().removeChildren();
}


void GuiManager::recreateInGameMenu()
{
  hideInGameGui();
  showInGameGui();
}

void GuiManager::showInGameGui()
{
  CONTRACT_EXPECT(!d_inGameGui);

  d_inGameGui = &GuiCreator::createControl(d_game.getForm());

  const bool godMode = SAFE_DEREF(d_session).isGodMode();

  auto& godModeLayout = GuiCreator::createLayout(*d_inGameGui);
  godModeLayout.setPosition({ 0, (float)getResolution().y });
  godModeLayout.setAlign(Dx::LayoutAlign::LeftToRight_BottomSide);

  {
    auto& btn = GuiCreator::createButton(godModeLayout);
    btn.setTextureName(godMode ? "f1_enabled.png" : "f1_disabled.png");
    if (!godMode)
      btn.setOnPress(std::bind(&GuiManager::onBtnGodMode, this));
  }

  {
    auto& btn = GuiCreator::createButton(godModeLayout);
    btn.setTextureName(godMode ? "f2_disabled.png" : "f2_enabled.png");
    if (godMode)
      btn.setOnPress(std::bind(&GuiManager::onBtnLiveMode, this));
  }

  d_overlay = d_session->getOverlay();
  if (d_overlay)
    showOverlayUI();
}

void GuiManager::hideInGameGui()
{
  CONTRACT_EXPECT(d_inGameGui);

  hideOverlayUI();
  hideGodModeBuildMenu();
  hideCtxMenu();

  d_inGameGui->setParent(nullptr);
  d_inGameGui = nullptr;
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


void GuiManager::onResumeGame()
{
  CONTRACT_EXPECT(d_session);
  d_session->unpause();
}

void GuiManager::onExitToMenu()
{
  hidePauseMenu();
  d_game.closeSession();
}


void GuiManager::onOverlaySet(const IOverlay* i_overlay)
{
  d_overlay = i_overlay;

  hideOverlayUI();

  if (i_overlay)
    showOverlayUI();
}

void GuiManager::showOverlayUI()
{
  if (!d_inGameGui)
    return;

  CONTRACT_EXPECT(d_overlay);
  CONTRACT_EXPECT(!d_overlayPanel);

  d_overlayPanel = &GuiCreator::createPanel(*d_inGameGui);
  d_overlayPanel->setTexture(Dx::TextureUtils::getTexture("White.png"));
  d_overlayPanel->setColor({ 0.5f, 0.5f, 0.5f, 0.5f });
  d_overlayPanel->setSize({ 200, 48 });
  d_overlayPanel->setPosition({ getResolution().x - d_overlayPanel->getSize().x, 0 });

  auto& layout = GuiCreator::createLayout(*d_overlayPanel);
  layout.setSize(d_overlayPanel->getSize());
  layout.setAlign(Dx::LayoutAlign::TopToBottom_Center);
  
  auto& label = GuiCreator::createLabel(layout);
  label.setText(getOverlayName(d_overlay->getType()));

  if (d_overlay->getType() == OverlayType::Temp)
    showOverlayHintTemp();
}

void GuiManager::hideOverlayUI()
{
  if (d_overlayPanel)
  {
    hideOverlayHint();

    d_overlayPanel->setParent(nullptr);
    d_overlayPanel = nullptr;
  }
}

void GuiManager::showOverlayHintTemp()
{
  CONTRACT_EXPECT(!d_overlayHint);

  d_overlayHint = &GuiCreator::createPanel(*d_inGameGui);
  d_overlayHint->setTexture(Dx::TextureUtils::getTexture("White.png"));
  d_overlayHint->setColor({ 0.6f, 0.47f, 0.31f, 0.8f });

  d_overlayHintLabel = &GuiCreator::createLabel(*d_overlayHint);
  d_overlayHintLabel->setFont(Fonts::getInGameHintsFont());

  updateOverlayHint();
}

void GuiManager::hideOverlayHint()
{
  if (d_overlayHint)
  {
    d_overlayHint->setParent(nullptr);
    d_overlayHint = nullptr;
  }
}

void GuiManager::updateOverlayHint()
{
  CONTRACT_EXPECT(d_overlay);
  CONTRACT_EXPECT(d_overlayHint);
  CONTRACT_EXPECT(d_overlayHintLabel);
  CONTRACT_EXPECT(d_session);

  CONTRACT_EXPECT(d_overlay->getType() == OverlayType::Temp);

  const auto& mousePos = Dx::CursorUtils::getPosition();
  d_overlayHint->setPosition(mousePos.getVector<float>() + Sdk::Vector2F{ 8, 0 });

  const auto tileCoords = TileUtils::getTileCoordsUnderCursor(d_session->getCamera());
  const auto& currentLocation = SAFE_DEREF(d_session->getCurrentLocation());
  const auto* tile = currentLocation.getTile(tileCoords);
  const auto tempString = tile ? Sdk::toString(tile->getT(), 2) + " C" : "N/A";
  d_overlayHintLabel->setText("T: " + tempString);

  const auto stringRect = SAFE_DEREF(d_overlayHintLabel->getFontResource()).getStringRect(d_overlayHintLabel->getText());
  d_overlayHint->setSize(stringRect.size().getVector<float>() + Sdk::Vector2F(4, 0));
}


void GuiManager::showCtxMenu(const CtxMenuContent& i_ctxMenuContent)
{
  hideCtxMenu();

  d_ctxMenu = &GuiCreator::createPanel(d_game.getForm());
  d_ctxMenu->setTexture(Dx::TextureUtils::getTexture("White.png"));
  d_ctxMenu->setColor({ 0.6f, 0.47f, 0.31f, 0.8f });
  d_ctxMenu->setPosition(Dx::CursorUtils::getPosition().getVector<float>());

  auto& label = GuiCreator::createLabel(*d_ctxMenu);
  label.setFont(Fonts::getInGameHintsFont());
  label.setText(i_ctxMenuContent.getDescription());

  const auto stringRect = SAFE_DEREF(label.getFontResource()).getStringRect(label.getText());
  d_ctxMenu->setSize(stringRect.size().getVector<float>() + Sdk::Vector2F(4, 0));
}

void GuiManager::hideCtxMenu()
{
  if (d_ctxMenu)
  {
    d_ctxMenu->setParent(nullptr);
    d_ctxMenu = nullptr;
  }
}
