#include "stdafx.h"
#include "PrototypesCollection.h"

#include "PrototypeLoader.h"


namespace
{
  PrototypesMap d_allPrototypes;
  PrototypesMap d_avatarPrototypes;
  PrototypesMap d_mountPrototypes;
  PrototypesMap d_structurePrototypes;
  PrototypesMap d_objectPrototypes;

} // anonym NS


void PrototypesCollection::load(const fs::path& i_prototypesFolder)
{
  CONTRACT_EXPECT(fs::exists(i_prototypesFolder));

  clearPrototypes();

  loadAvatars(i_prototypesFolder);
  loadMounts(i_prototypesFolder);
  loadStructures(i_prototypesFolder);
  loadObjects(i_prototypesFolder);
}


void PrototypesCollection::clearPrototypes()
{
  d_allPrototypes.clear();
  d_avatarPrototypes.clear();
  d_mountPrototypes.clear();
  d_structurePrototypes.clear();
  d_objectPrototypes.clear();
}


void PrototypesCollection::loadAvatars(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "avatars.json";
  const auto prototypes = PrototypeLoader::loadAvatars(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototype : prototypes)
  {
    d_allPrototypes[SAFE_DEREF(prototype).name] = prototype;
    d_avatarPrototypes[SAFE_DEREF(prototype).name] = prototype;
  }
}

void PrototypesCollection::loadMounts(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "mounts.json";
  const auto prototypes = PrototypeLoader::loadMounts(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototype : prototypes)
  {
    d_allPrototypes[SAFE_DEREF(prototype).name] = prototype;
    d_mountPrototypes[SAFE_DEREF(prototype).name] = prototype;
  }
}

void PrototypesCollection::loadStructures(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "structures.json";
  const auto prototypes = PrototypeLoader::loadStructures(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototype : prototypes)
  {
    d_allPrototypes[SAFE_DEREF(prototype).name] = prototype;
    d_structurePrototypes[SAFE_DEREF(prototype).name] = prototype;
  }
}

void PrototypesCollection::loadObjects(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "objects.json";
  const auto prototypes = PrototypeLoader::loadObjects(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototype : prototypes)
  {
    d_allPrototypes[SAFE_DEREF(prototype).name] = prototype;
    d_objectPrototypes[SAFE_DEREF(prototype).name] = prototype;
  }
}


PrototypePtr PrototypesCollection::getPrototype(const PrototypeName& i_name)
{
  return d_allPrototypes.at(i_name);
}

PrototypePtr PrototypesCollection::getAvatarPrototype(const PrototypeName& i_name)
{
  return d_avatarPrototypes.at(i_name);
}

PrototypePtr PrototypesCollection::getMountPrototype(const PrototypeName& i_name)
{
  return d_mountPrototypes.at(i_name);
}

PrototypePtr PrototypesCollection::getStructurePrototype(const PrototypeName& i_name)
{
  return d_structurePrototypes.at(i_name);
}

PrototypePtr PrototypesCollection::getObjectPrototype(const PrototypeName& i_name)
{
  return d_objectPrototypes.at(i_name);
}


const PrototypesMap& PrototypesCollection::getAllPrototypes()
{
  return d_allPrototypes;
}

const PrototypesMap& PrototypesCollection::getAvatarPrototypes()
{
  return d_avatarPrototypes;
}

const PrototypesMap& PrototypesCollection::getMountPrototypes()
{
  return d_mountPrototypes;
}

const PrototypesMap& PrototypesCollection::getStructurePrototypes()
{
  return d_structurePrototypes;
}

const PrototypesMap& PrototypesCollection::getObjectPrototypes()
{
  return d_objectPrototypes;
}
