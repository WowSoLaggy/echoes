#include "stdafx.h"
#include "PrototypesCollection.h"

#include "StructurePrototypeLoader.h"


namespace
{
  std::unordered_map<PrototypeName, StructurePrototype> d_structurePrototypes;

} // anonym NS


void PrototypesCollection::load(const fs::path& i_prototypesFolder)
{
  CONTRACT_EXPECT(fs::exists(i_prototypesFolder));

  const std::string StructuresPrototypeFileName = "Structures.json";
  const auto structurePrototypes = StructurePrototypeLoader::load(i_prototypesFolder / StructuresPrototypeFileName);

  for (const auto& prototype : structurePrototypes)
    d_structurePrototypes[prototype.name] = prototype;
}


const StructurePrototype& PrototypesCollection::getStructurePrototype(const PrototypeName& i_name)
{
  return d_structurePrototypes.at(i_name);
}


const std::unordered_map<PrototypeName, StructurePrototype>& PrototypesCollection::getStructurePrototypes()
{
  return d_structurePrototypes;
}
