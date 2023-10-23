#include "stdafx.h"
#include "Tile.h"

#include "Structure.h"

#include <LaggySdk/JsonSerializer.h>


void Tile::pushFields()
{
  for (auto& [layer, structurePtr] : d_layers)
    pushObject(LayerStr::toString(layer), SAFE_DEREF(structurePtr));
}

Sdk::FieldHandled Tile::onFieldNotFound(const std::string& i_name, const Json::Value& i_json)
{
  const auto layer = LayerStr::fromString(i_name);

  auto structurePtr = std::make_shared<Structure>();
  Sdk::JsonSerializer::deserialize(*structurePtr, i_json);

  d_layers[layer] = std::move(structurePtr);

  return true;
}


void Tile::update(const double i_dt)
{
  for (auto& [_, structurePtr] : d_layers)
    SAFE_DEREF(structurePtr).update(i_dt);
}


const LayersMap& Tile::getLayers() const
{
  return d_layers;
}


const StructurePtr Tile::getStructure(Layer i_layer) const
{
  if (d_layers.contains(i_layer))
    return d_layers.at(i_layer);
  return nullptr;
}


void Tile::setStructure(const Layer i_layer, StructurePtr i_structure)
{
  CONTRACT_EXPECT(i_structure);
  CONTRACT_EXPECT(d_layers[i_layer] == nullptr);
  d_layers[i_layer] = i_structure;
}

void Tile::resetStructure(const Layer i_layer)
{
  d_layers.erase(i_layer);
}


double Tile::getT() const
{
  return d_temperature;
}

void Tile::setT(const double i_t)
{
  d_temperature = i_t;
}


Dx::thd::VolumeUnit& Tile::getVolumeUnit()
{
  return d_volumeUnit;
}

const Dx::thd::VolumeUnit& Tile::getVolumeUnit() const
{
  return d_volumeUnit;
}
