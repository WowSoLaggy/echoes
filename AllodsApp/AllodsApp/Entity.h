#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"

#include <LaggyDx/Animation2Player.h>

#include <LaggySdk/ISerializable.h>
#include <LaggySdk/Size.h>


class Entity : public Sdk::ISerializable
{
public:
  Entity();
  Entity(PrototypePtr i_prototype);

  virtual void pushFields() override;
  virtual void onFieldNotFound(const std::string& i_name, const Json::Value& i_json) override;

  void update(double i_dt);

  void setPrototype(PrototypePtr i_prototype);
  [[nodiscard]] bool hasPrototype() const;
  [[nodiscard]] const Prototype& getPrototype() const;

  [[nodiscard]] const Sdk::Size2I& getSize() const;

  [[nodiscard]] Dx::Animation2Player& getAnimationPlayer();
  [[nodiscard]] const Dx::Animation2Player& getAnimationPlayer() const;

  void setBehaviorModel(BehaviorModelPtr i_model);
  void resetBehaviorModel();
  [[nodiscard]] BehaviorModelPtr getBehaviorModel() const;

private:
  PrototypePtr d_prototype;
  Dx::Animation2Player d_animationPlayer;
  BehaviorModelPtr d_behaviorModel;
};
