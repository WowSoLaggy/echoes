#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"

#include <LaggyDx/Animation2Player.h>
#include <LaggyDx/IThdObject.h>

#include <LaggySdk/ISerializable.h>
#include <LaggySdk/Size.h>


class Entity : public Sdk::ISerializable, public Dx::thd::IThdObject
{
public:
  Entity();
  explicit Entity(PrototypePtr i_prototype);

  virtual void pushFields() override;
  virtual Sdk::FieldHandled onFieldNotFound(const std::string& i_name, const Json::Value& i_json) override;
  virtual void onDeserialized() override;

  void update(double i_dt);

  void setPrototype(PrototypePtr i_prototype, bool i_setBehaviorModel = true);
  [[nodiscard]] bool hasPrototype() const;
  [[nodiscard]] const Prototype& getPrototype() const;

  [[nodiscard]] const Sdk::Size2I& getSize() const;

  [[nodiscard]] Dx::Animation2Player& getAnimationPlayer();
  [[nodiscard]] const Dx::Animation2Player& getAnimationPlayer() const;

  void setBehaviorModel(BehaviorModelPtr i_model);
  void resetBehaviorModel();
  [[nodiscard]] BehaviorModelPtr getBehaviorModel() const;
  
  template <typename T>
  [[nodiscard]] T* getBehaviorModel() const
  {
    return dynamic_cast<T*>(d_behaviorModel.get());
  }

  [[nodiscard]] double getMass() const;

  virtual void setTemperature(double i_temperature) override;
  [[nodiscard]] virtual double getTemperature() const override;
  [[nodiscard]] virtual double getThermalConductivity() const override;
  [[nodiscard]] virtual double getHeatCapacity() const override;

private:
  PrototypePtr d_prototype;
  Dx::Animation2Player d_animationPlayer;
  BehaviorModelPtr d_behaviorModel;

  double d_temperature = 0;
};
