#pragma once


enum class Layer : int32_t
{
  Panneling = 0,
  Floor,

  Count
};


const std::vector<Layer>& getLayers();
