#pragma once

#include "Fwd.h"


class EntityUtils
{
public:
  static EntityPtr getEntityUnderCursor(const Session& i_session);

private:
  EntityUtils() = delete;
};
