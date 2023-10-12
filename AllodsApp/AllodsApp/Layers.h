#pragma once


enum class Layer : int32_t
{
  Lowest = 0,

  Panneling = Lowest,
  Floor,
  Wall,
  Furniture,

  Count
};


const std::vector<Layer>& getLayers();
