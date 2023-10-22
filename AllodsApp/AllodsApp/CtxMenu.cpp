#include "stdafx.h"
#include "CtxMenu.h"

#include "BehaviorAction.h"
#include "CtxMenuContent.h"
#include "Fonts.h"
#include "GuiCreator.h"

#include <LaggyDx/Button.h>
#include <LaggyDx/IFontResource.h>
#include <LaggyDx/Label.h>
#include <LaggyDx/Layout.h>
#include <LaggyDx/TextureUtils.h>


void CtxMenu::setContext(const CtxMenuContent& i_ctxMenuContent)
{
  setTexture(Dx::TextureUtils::getTexture("White.png"));
  setColor({ 0.6f, 0.47f, 0.31f, 0.8f });

  auto& layout = GuiCreator::createLayout(*this);
  layout.setAlign(Dx::LayoutAlign::TopToBottom_LeftSide);
  layout.setOffsetBetweenElements(0);

  d_label = &GuiCreator::createLabel(layout);
  d_label->setFont(Fonts::getInGameHintsFont());
  d_label->setText(i_ctxMenuContent.getDescription());

  // Actions

  for (const auto& actionPtr : i_ctxMenuContent.getActions())
  {
    const auto& action = SAFE_DEREF(actionPtr);

    auto& button = GuiCreator::createCtxMenuButton(layout);

    std::string text = action.getDevOnly() ? "[Dev] " : "";
    text += action.getName();
    button.setText(std::move(text));
    button.setOnPress(action.getFunction());
  }

  // Final menu size

  const auto stringRect = SAFE_DEREF(d_label->getFontResource()).getStringRect(d_label->getText());
  setSize(stringRect.size().getVector<float>() + Sdk::Vector2F(4, 0));
}


void CtxMenu::setText()
{
}

void CtxMenu::setActions()
{
}
