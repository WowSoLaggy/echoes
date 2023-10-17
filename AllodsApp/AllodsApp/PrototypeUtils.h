#pragma once

#include "Fwd.h"


class PrototypeUtils
{
public:

  template <typename T>
  static T& convert(PrototypePtr i_prototypePtr)
  {
    return SAFE_DEREF(dynamic_cast<T*>(i_prototypePtr.get()));
  }

};
