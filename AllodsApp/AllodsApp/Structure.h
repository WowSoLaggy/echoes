#pragma once

#include "Fixture.h"
#include "TileBaseEntity.h"


class Structure : public TileBaseEntity
{
public:
  Structure();
  Structure(PrototypePtr i_prototype);

  virtual void pushFields() override;

  [[nodiscard]] const StructurePrototype& getStructurePrototype() const;

  [[nodiscard]] FixturePtr getFixture() const;

  bool isAirTight() const;

private:
  FixturePtr d_fixture;
};
