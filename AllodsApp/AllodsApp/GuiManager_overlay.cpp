#include "stdafx.h"
#include "GuiManager.h"

#include "Fonts.h"
#include "GuiCreator.h"
#include "IOverlay.h"
#include "Location.h"
#include "Session.h"
#include "TileUtils.h"

#include <LaggyDx/CursorUtils.h>
#include <LaggyDx/IFontResource.h>
#include <LaggyDx/Label.h>
#include <LaggyDx/Layout.h>
#include <LaggyDx/Panel.h>


namespace
{
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
  d_overlayPanel->setTexture("white.png");
  d_overlayPanel->setColor({ 0.5f, 0.5f, 0.5f, 0.5f });
  d_overlayPanel->setSize({ 200, 48 });
  d_overlayPanel->setPosition({ getResolution().x - d_overlayPanel->getSize().x, 0 });

  auto& layout = GuiCreator::createLayout(*d_overlayPanel);
  layout.setSize(d_overlayPanel->getSize());
  layout.setAlign(Dx::LayoutAlign::TopToBottom_Center);

  auto& label = GuiCreator::createLabel(layout);
  label.setText(getOverlayName(d_overlay->getType()));

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
  d_overlayHint->setTexture("white.png");
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

  const auto& mousePos = Dx::CursorUtils::getPosition();
  d_overlayHint->setPosition(mousePos.getVector<float>() + Sdk::Vector2F{ 8, 0 });

  const auto tileCoords = TileUtils::getTileCoordsUnderCursor(d_session->getCamera());
  const auto hintText = d_overlay->getHint(tileCoords);
  d_overlayHintLabel->setText(hintText);

  const auto stringRect = SAFE_DEREF(d_overlayHintLabel->getFontResource()).getStringRect(hintText);
  d_overlayHint->setSize(stringRect.size().getVector<float>() + Sdk::Vector2F(4, 0));
}
