#pragma once

#include "Fwd.h"


class StructureUtils
{
public:
  static StructurePtr getStructureUnderCursor(const Session& i_session);

private:
  StructureUtils() = delete;
};
