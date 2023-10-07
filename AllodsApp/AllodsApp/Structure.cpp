#include "stdafx.h"
#include "Structure.h"

#include "Prototypes.h"


Structure::Structure(const StructurePrototype& i_prototype)
  : Entity(i_prototype)
{
  if (i_prototype.fixture)
    d_fixture = std::make_shared<Fixture>();
}


const StructurePrototype& Structure::getStructurePrototype() const
{
  return dynamic_cast<const StructurePrototype&>(Entity::getPrototype());
}


FixturePtr Structure::getFixture() const
{
  return d_fixture;
}
