#include "stdafx.h"
#include "Structure.h"


Structure::Structure(const StructurePrototype& i_prototype)
  : d_prototype(i_prototype)
{
  setBehaviorModel(IBehaviorModel::get(d_prototype.bahaviorModel, *this));
}


void Structure::update(const double i_dt)
{
  d_animationPlayer.update(i_dt);
}


const StructurePrototype& Structure::getPrototype() const
{
  return d_prototype;
}


Dx::Animation2Player& Structure::getAnimationPlayer()
{
  return d_animationPlayer;
}

const Dx::Animation2Player& Structure::getAnimationPlayer() const
{
  return d_animationPlayer;
}


void Structure::setBehaviorModel(BehaviorModelPtr i_model)
{
  d_behaviorModel = i_model;
}

BehaviorModelPtr Structure::getBehaviorModel() const
{
  return d_behaviorModel;
}
