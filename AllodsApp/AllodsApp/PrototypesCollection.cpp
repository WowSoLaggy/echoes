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

  void checkNameIsNotDuplicated(const std::string& i_name)
  {
    CONTRACT_ASSERT(!d_allPrototypes.contains(i_name), "Duplicated prototype name: " + i_name);
  }

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

  for (const auto& prototypePtr : prototypes)
  {
    const auto& prototype = SAFE_DEREF(prototypePtr);
    checkNameIsNotDuplicated(prototype.name);

    d_allPrototypes[prototype.name] = prototypePtr;
    d_avatarPrototypes[prototype.name] = prototypePtr;
  }
}

void PrototypesCollection::loadMounts(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "mounts.json";
  const auto prototypes = PrototypeLoader::loadMounts(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototypePtr : prototypes)
  {
    const auto& prototype = SAFE_DEREF(prototypePtr);
    checkNameIsNotDuplicated(prototype.name);

    d_allPrototypes[prototype.name] = prototypePtr;
    d_mountPrototypes[prototype.name] = prototypePtr;
  }
}

void PrototypesCollection::loadStructures(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "structures.json";
  const auto prototypes = PrototypeLoader::loadStructures(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototypePtr : prototypes)
  {
    const auto& prototype = SAFE_DEREF(prototypePtr);
    checkNameIsNotDuplicated(prototype.name);

    d_allPrototypes[prototype.name] = prototypePtr;
    d_structurePrototypes[prototype.name] = prototypePtr;
  }
}

void PrototypesCollection::loadObjects(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "objects.json";
  const auto prototypes = PrototypeLoader::loadObjects(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototypePtr : prototypes)
  {
    const auto& prototype = SAFE_DEREF(prototypePtr);
    checkNameIsNotDuplicated(prototype.name);

    d_allPrototypes[prototype.name] = prototypePtr;
    d_objectPrototypes[prototype.name] = prototypePtr;
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
