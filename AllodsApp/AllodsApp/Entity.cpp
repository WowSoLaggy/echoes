#include "stdafx.h"
#include "Entity.h"

#include "AnimationUtils.h"
#include "Materials.h"
#include "Prototypes.h"
#include "PrototypesCollection.h"

#include <LaggyDx/ImageDescription.h>


namespace
{
  const std::string PrototypeNameField = "prototypeName";
  const std::string BehaviorModelField = "behaviorModel";

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
  pushObject("animationPlayer", d_animationPlayer);
  
  if (hasPrototype())
    pushField(PrototypeNameField, getPrototype().name);
  
  if (d_behaviorModel)
    pushObject("behaviorModel", *d_behaviorModel);
}

Sdk::FieldHandled Entity::onFieldNotFound(const std::string& i_name, const Json::Value& i_json)
{
  if (i_name == PrototypeNameField)
  {
    const std::string prototypeName = i_json.asString();
    const auto prototype = PrototypesCollection::getPrototype(prototypeName);
    setPrototype(prototype, false);
    return true;
  }
  else if (i_name == BehaviorModelField)
  {
    setBehaviorModel(IBehaviorModel::deserialize(i_json, *this));
    return true;
  }

  return false;
}

void Entity::onDeserialized()
{
  // Prototype was not deserialized
  CONTRACT_ENSURE(hasPrototype());

  const auto animationToPlay = d_animationPlayer.getAnimationName();
  if (!animationToPlay.empty())
    AnimationUtils::playAnimation(*this, animationToPlay, d_animationPlayer.getTimesLeft(), false);
}


void Entity::setPrototype(PrototypePtr i_prototype, const bool i_setBehaviorModel)
{
  d_prototype = i_prototype;

  if (i_setBehaviorModel)
  {
    if (d_prototype)
      setBehaviorModel(IBehaviorModel::get(getPrototype().bahaviorModel, *this));
    else
      resetBehaviorModel();
  }
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
  if (d_behaviorModel)
    d_behaviorModel->update(i_dt);
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


double Entity::getMass() const
{
  return getPrototype().mass;
}


void Entity::setTemperature(const double i_temperature)
{
  d_temperature = i_temperature;
}

std::optional<double> Entity::getTemperature() const
{
  return d_temperature;
}

double Entity::getThermalConductivity() const
{
  const auto material = getPrototype().material;
  return getMaterialThermalConductivity(material);
}

double Entity::getHeatCapacity() const
{
  const auto material = getPrototype().material;
  return getMaterialHeatCapacity(material) * getMass();
}
