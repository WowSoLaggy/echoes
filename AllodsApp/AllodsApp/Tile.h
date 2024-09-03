#pragma once

#include "Fwd.h"
#include "GasThd.h"
#include "Layers.h"

#include <LaggySdk/ISerializable.h>
#include <LaggySdk/Vector.h>


using LayersMap = std::map<Layer, StructurePtr>;


class Tile : public Sdk::ISerializable
{
public:
  virtual void pushFields() override;
  virtual Sdk::FieldHandled onFieldNotFound(const std::string& i_name, const Json::Value& i_json);

  void update(double i_dt);

  const LayersMap& getLayers() const;
  const Objects& getObjects() const;
  const Avatars& getAvatars() const;
  std::vector<Entity*> getEntities();
  const std::vector<Entity*> getEntities() const;

  const StructurePtr getStructure(Layer i_layer) const;
  void setStructure(Layer i_layer, StructurePtr i_structure);
  void resetStructure(Layer i_layer);

  void addObject(ObjectPtr i_object);
  void addAvatar(AvatarPtr i_avatar);
  void removeObject(const Object& i_object);
  void removeAvatar(const Avatar& i_avatar);

  bool isSpaceExposed() const;
  bool isAirTight() const;

  GasThd& getGasUnitThd();
  const GasThd& getGasUnitThd() const;

private:
  LayersMap d_layers;
  Avatars d_avatars;
  Objects d_objects;

  double d_temperature = 0;
  GasThd d_gasUnitThd;
};
