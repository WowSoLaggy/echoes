#include "stdafx.h"
#include "PrototypesCollection.h"

#include "PrototypeLoader.h"


namespace
{
  AvatarPrototypesMap d_avatarPrototypes;
  MountPrototypesMap d_mountPrototypes;
  StructurePrototypesMap d_structurePrototypes;
  ObjectPrototypesMap d_objectPrototypes;

} // anonym NS


void PrototypesCollection::load(const fs::path& i_prototypesFolder)
{
  CONTRACT_EXPECT(fs::exists(i_prototypesFolder));

  loadAvatars(i_prototypesFolder);
  loadMounts(i_prototypesFolder);
  loadStructures(i_prototypesFolder);
  loadObjects(i_prototypesFolder);
}


void PrototypesCollection::loadAvatars(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "avatars.json";
  const auto prototypes = PrototypeLoader::loadAvatars(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototype : prototypes)
    d_avatarPrototypes[prototype.name] = prototype;
}

void PrototypesCollection::loadMounts(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "mounts.json";
  const auto prototypes = PrototypeLoader::loadMounts(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototype : prototypes)
    d_mountPrototypes[prototype.name] = prototype;
}

void PrototypesCollection::loadStructures(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "structures.json";
  const auto prototypes = PrototypeLoader::loadStructures(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototype : prototypes)
    d_structurePrototypes[prototype.name] = prototype;
}

void PrototypesCollection::loadObjects(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "objects.json";
  const auto prototypes = PrototypeLoader::loadObjects(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototype : prototypes)
    d_objectPrototypes[prototype.name] = prototype;
}


const AvatarPrototype& PrototypesCollection::getAvatarPrototype(const PrototypeName& i_name)
{
  return d_avatarPrototypes.at(i_name);
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


const AvatarPrototypesMap& PrototypesCollection::getAvatarPrototypes()
{
  return d_avatarPrototypes;
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
