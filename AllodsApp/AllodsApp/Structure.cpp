#include "stdafx.h"
#include "Structure.h"


Structure::Structure(const StructurePrototype& i_prototype)
  : d_prototype(i_prototype)
{
}


const StructurePrototype& Structure::getPrototype() const
{
  return d_prototype;
}
