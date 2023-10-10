#include "stdafx.h"
#include "PrototypesCollection.h"

#include "PrototypeLoader.h"


namespace
{
  MountPrototypesMap d_mountPrototypes;
  StructurePrototypesMap d_structurePrototypes;
  ObjectPrototypesMap d_objectPrototypes;

} // anonym NS


void PrototypesCollection::load(const fs::path& i_prototypesFolder)
{
  CONTRACT_EXPECT(fs::exists(i_prototypesFolder));

  loadMounts(i_prototypesFolder);
  loadStructures(i_prototypesFolder);
  loadObjects(i_prototypesFolder);
}


void PrototypesCollection::loadMounts(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "mounts.json";
  const auto structurePrototypes = PrototypeLoader::loadMounts(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototype : structurePrototypes)
    d_mountPrototypes[prototype.name] = prototype;
}

void PrototypesCollection::loadStructures(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "structures.json";
  const auto structurePrototypes = PrototypeLoader::loadStructures(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototype : structurePrototypes)
    d_structurePrototypes[prototype.name] = prototype;
}

void PrototypesCollection::loadObjects(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "objects.json";
  const auto structurePrototypes = PrototypeLoader::loadObjects(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototype : structurePrototypes)
    d_objectPrototypes[prototype.name] = prototype;
}


const MountPrototype& PrototypesCollection::getMountPrototype(const PrototypeName& i_name)
{
  return d_mountPrototypes.at(i_name);
}

const StructurePrototype& PrototypesCollection::getStructurePrototype(const PrototypeName& i_name)
{
  return d_structurePrototypes.at(i_name);
}

const ObjectPrototype& PrototypesCollection::getObjectPrototype(const PrototypeName& i_name)
{
  return d_objectPrototypes.at(i_name);
}


const MountPrototypesMap& PrototypesCollection::getMountPrototypes()
{
  return d_mountPrototypes;
}

const StructurePrototypesMap& PrototypesCollection::getStructurePrototypes()
{
  return d_structurePrototypes;
}

const ObjectPrototypesMap& PrototypesCollection::getObjectPrototypes()
{
  return d_objectPrototypes;
}
