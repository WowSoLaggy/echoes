#include "stdafx.h"
#include "Entity.h"

#include "Prototypes.h"


Entity::Entity(const Prototype& i_prototype)
  : d_prototype(i_prototype)
{
  setBehaviorModel(IBehaviorModel::get(i_prototype.bahaviorModel, *this));
}


const Prototype& Entity::getPrototype() const
{
  return d_prototype;
}


void Entity::update(const double i_dt)
{
  d_animationPlayer.update(i_dt);
}


Dx::Animation2Player& Entity::getAnimationPlayer()
{
  return d_animationPlayer;
}

const Dx::Animation2Player& Entity::getAnimationPlayer() const
{
  return d_animationPlayer;
}


void Entity::setBehaviorModel(BehaviorModelPtr i_model)
{
  d_behaviorModel = i_model;
}

BehaviorModelPtr Entity::getBehaviorModel() const
{
  return d_behaviorModel;
}
