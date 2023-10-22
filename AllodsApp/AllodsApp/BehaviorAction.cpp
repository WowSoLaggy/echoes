#include "stdafx.h"
#include "BehaviorAction.h"


BehaviorAction::BehaviorAction(std::string i_name, BehaviorFunction i_function, bool i_devOnly)
  : d_name(std::move(i_name))
  , d_function(i_function)
  , d_devOnly(i_devOnly)
{
}


const std::string& BehaviorAction::getName() const
{
  return d_name;
}

bool BehaviorAction::getDevOnly() const
{
  return d_devOnly;
}

BehaviorFunction BehaviorAction::getFunction() const
{
  return d_function;
}
