#pragma once

#include "Fwd.h"

#include <LaggySdk/Vector.h>


class ItemPicker
{
public:
  ItemPicker(const Session& i_session);

  EntityPtr pick() const;
  EntityPtr pick(const Sdk::Vector2I& i_screenPos) const;

private:
  const Session& d_session;

  EntityPtr pickObject(const Sdk::Vector2I& i_screenPos) const;
  EntityPtr pickStructureOrMount(const Sdk::Vector2I& i_screenPos) const;
};
