#include "stdafx.h"
#include "Structure.h"

#include "Prototypes.h"


Structure::Structure()
{
}

Structure::Structure(PrototypePtr i_prototype)
  : TileBaseEntity(i_prototype)
{
  if (getStructurePrototype().fixture)
    d_fixture = std::make_shared<Fixture>();
}


void Structure::pushFields()
{
  TileBaseEntity::pushFields();

  if (d_fixture)
    pushObject("fixture", *d_fixture);
}


const StructurePrototype& Structure::getStructurePrototype() const
{
  return dynamic_cast<const StructurePrototype&>(getPrototype());
}


FixturePtr Structure::getFixture() const
{
  return d_fixture;
}
