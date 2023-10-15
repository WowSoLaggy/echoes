#include "stdafx.h"
#include "Layers.h"


namespace
{
  const std::unordered_map<Layer, std::string> LayersStrings {
    { Layer::Panneling, "Panneling" },
    { Layer::Floor, "Floor" },
    { Layer::Wall, "Wall" },
    { Layer::Furniture, "Furniture" },
  };

} // anonym NS


DEFINE_ENUM_STR(Layer, LayersStrings)


const std::vector<Layer>& getLayers()
{
  const auto generateVector = []()
  {
    std::vector<Layer> layers;
    for (int i = 0; i < static_cast<int>(Layer::Count); ++i)
      layers.push_back(static_cast<Layer>(i));
    return layers;
  };

  static const std::vector<Layer> layers = generateVector();
  return layers;
}
