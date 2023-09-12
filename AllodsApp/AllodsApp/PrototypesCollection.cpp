#include "stdafx.h"
#include "PrototypesCollection.h"

#include "StructurePrototypeLoader.h"


void PrototypesCollection::load(const fs::path& i_prototypesFolder)
{
  CONTRACT_EXPECT(fs::exists(i_prototypesFolder));

  const std::string StructuresPrototypeFileName = "Structures.json";
  const auto structurePrototypes = StructurePrototypeLoader::load(i_prototypesFolder / StructuresPrototypeFileName);

  for (const auto& prototype : structurePrototypes)
    d_structurePrototypes[prototype.name] = prototype;
}


const StructurePrototype& PrototypesCollection::getStructurePrototype(const std::string& i_name) const
{
  return d_structurePrototypes.at(i_name);
}
