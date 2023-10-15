#pragma once

#include "Fwd.h"
#include "Layers.h"

#include <LaggySdk/ISerializable.h>
#include <LaggySdk/Vector.h>


using LayersMap = std::map<Layer, StructurePtr>;


class Tile : public Sdk::ISerializable
{
public:
  virtual void pushFields() override;

  void update(double i_dt);

  const LayersMap& getLayers() const;

  const StructurePtr getStructure(Layer i_layer) const;

  void setStructure(Layer i_layer, StructurePtr i_structure);
  void resetStructure(Layer i_layer);

  double getT() const;
  void setT(double i_t);

private:
  LayersMap d_layers;

  double d_temperature = 0;
};

using Tiles = std::unordered_map<TileCoord, Tile, Sdk::Vector2_hash>;
