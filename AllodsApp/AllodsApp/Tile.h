#pragma once

#include "Fwd.h"
#include "Layers.h"

#include <LaggyDx/VolumeUnit.h>

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

  const StructurePtr getStructure(Layer i_layer) const;

  void setStructure(Layer i_layer, StructurePtr i_structure);
  void resetStructure(Layer i_layer);

  double getT() const;
  void setT(double i_t);

  Dx::thd::VolumeUnit& getVolumeUnit();
  const Dx::thd::VolumeUnit& getVolumeUnit() const;

private:
  LayersMap d_layers;

  double d_temperature = 0;
  Dx::thd::VolumeUnit d_volumeUnit;
};
