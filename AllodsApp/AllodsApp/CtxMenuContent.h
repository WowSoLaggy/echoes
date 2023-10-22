#pragma once

#include "Fwd.h"


class CtxMenuContent
{
public:
  CtxMenuContent(const Entity& i_entity, bool i_devMode);

  const std::string& getDescription() const;
  const BehaviorActions& getActions() const;

private:
  std::string d_description;
  BehaviorActions d_actions;
};
