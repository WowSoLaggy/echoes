#pragma once

#include <LaggySdk/EnumStr.h>


enum class Layer : int32_t
{
  Lowest = 0,

  Panneling = Lowest,
  Floor,
  Wall,
  Furniture,

  Count
};



DECLARE_ENUM_STR(Layer)


const std::vector<Layer>& getLayers();
