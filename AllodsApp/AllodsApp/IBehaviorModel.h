#pragma once

#include "BehaviorModels.h"
#include "Fwd.h"

#include <LaggySdk/ISerializable.h>
#include <LaggySdk/json.h>


class IBehaviorModel : public Sdk::ISerializable
{
public:
  static BehaviorModelPtr get(BehaviorModel i_model, Entity& i_entity);
  static BehaviorModelPtr deserialize(const Json::Value& i_json, Entity& i_entity);

public:
  virtual ~IBehaviorModel() = default;

  virtual void pushFields() override;
  virtual void interact();

  virtual BehaviorModel getModelType() const = 0;
  virtual std::string getDescription() const = 0;

private:
  int d_modelTypeCache = 0;
};
