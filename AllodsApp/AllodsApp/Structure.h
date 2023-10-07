#pragma once

#include "Entity.h"
#include "Fixture.h"
#include "Fwd.h"


class Structure : public Entity
{
public:
  Structure(const StructurePrototype& i_prototype);

  [[nodiscard]] const StructurePrototype& getStructurePrototype() const;

private:
  FixturePtr d_fixture;
};
