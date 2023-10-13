#pragma once

#include "TileBaseEntity.h"
#include "Fixture.h"
#include "Fwd.h"


class Structure : public TileBaseEntity
{
public:
  Structure(const StructurePrototype& i_prototype);

  [[nodiscard]] const StructurePrototype& getStructurePrototype() const;

  [[nodiscard]] FixturePtr getFixture() const;

private:
  FixturePtr d_fixture;
};
