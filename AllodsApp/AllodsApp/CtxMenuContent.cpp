#include "stdafx.h"
#include "CtxMenuContent.h"

#include "Entity.h"
#include "Prototypes.h"


CtxMenuContent::CtxMenuContent(const Entity& i_entity, bool i_devMode)
{
  d_description = i_entity.getPrototype().name;

  if (const auto behaviorModel = i_entity.getBehaviorModel())
  {
    d_description += "\n" + behaviorModel->getDescription();
    d_actions = behaviorModel->getActions(i_devMode);
  }
}


const std::string& CtxMenuContent::getDescription() const
{
  return d_description;
}

const BehaviorActions& CtxMenuContent::getActions() const
{
  return d_actions;
}
