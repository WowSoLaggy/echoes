#pragma once

#include "Fwd.h"
#include "GasThd.h"
#include "Layers.h"

#include <LaggySdk/EventHandler.h>
#include <LaggySdk/ISerializable.h>
#include <LaggySdk/Vector.h>


using LayersMap = std::map<Layer, StructurePtr>;


class Tile : public Sdk::ISerializable, public Sdk::EventHandler
{
public:
  virtual void pushFields() override;
  virtual Sdk::FieldHandled onFieldNotFound(const std::string& i_name, const Json::Value& i_json);

  virtual void processEvent(const Sdk::IEvent& i_event);

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
  void removeObject(Object& i_object);
  void removeAvatar(Avatar& i_avatar);

  bool isSpaceExposed() const;
  bool isAirTight() const;

  GasThd& getGasUnitThd();
  const GasThd& getGasUnitThd() const;

  void leakGasToSpace(double i_dt);

private:
  LayersMap d_layers;
  Avatars d_avatars;
  Objects d_objects;

  double d_temperature = 0;
  GasThd d_gasUnitThd;
};
