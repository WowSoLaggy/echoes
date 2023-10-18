#include "stdafx.h"
#include "Entity.h"

#include "Prototypes.h"
#include "PrototypesCollection.h"

#include <LaggyDx/ImageDescription.h>


namespace
{
  const std::string PrototypeNameField = "prototype_name";

} // anonym NS


Entity::Entity()
{
}

Entity::Entity(PrototypePtr i_prototype)
{
  setPrototype(i_prototype);
}


void Entity::pushFields()
{
  if (hasPrototype())
    pushField(PrototypeNameField, getPrototype().name);
  pushObject("animationPlayer", d_animationPlayer);
}

void Entity::onFieldNotFound(const std::string& i_name, const Json::Value& i_json)
{
  if (i_name == PrototypeNameField)
  {
    //PrototypesCollection::getAvatarPrototype();
  }
}


void Entity::setPrototype(PrototypePtr i_prototype)
{
  d_prototype = i_prototype;

  if (d_prototype)
    setBehaviorModel(IBehaviorModel::get(getPrototype().bahaviorModel, *this));
  else
    resetBehaviorModel();
}

bool Entity::hasPrototype() const
{
  return d_prototype.get();
}

const Prototype& Entity::getPrototype() const
{
  return SAFE_DEREF(d_prototype);
}


const Sdk::Size2I& Entity::getSize() const
{
  return SAFE_DEREF(getPrototype().texture).getDescription().frameSize;
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

void Entity::resetBehaviorModel()
{
  setBehaviorModel(nullptr);
}

BehaviorModelPtr Entity::getBehaviorModel() const
{
  return d_behaviorModel;
}
