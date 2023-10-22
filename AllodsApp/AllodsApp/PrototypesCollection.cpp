#include "stdafx.h"
#include "PrototypesCollection.h"

#include "PrototypeLoader.h"


namespace
{
  PrototypesMap g_allPrototypes;
  PrototypesMap g_avatarPrototypes;
  PrototypesMap g_mountPrototypes;
  PrototypesMap g_structurePrototypes;
  PrototypesMap g_objectPrototypes;

  void checkNameIsNotDuplicated(const std::string& i_name)
  {
    CONTRACT_ASSERT(!g_allPrototypes.contains(i_name), "Duplicated prototype name: " + i_name);
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
  g_allPrototypes.clear();
  g_avatarPrototypes.clear();
  g_mountPrototypes.clear();
  g_structurePrototypes.clear();
  g_objectPrototypes.clear();
}


void PrototypesCollection::loadAvatars(const fs::path& i_prototypesFolder)
{
  const std::string PrototypeFileName = "avatars.json";
  const auto prototypes = PrototypeLoader::loadAvatars(i_prototypesFolder / PrototypeFileName);

  for (const auto& prototypePtr : prototypes)
  {
    const auto& prototype = SAFE_DEREF(prototypePtr);
    checkNameIsNotDuplicated(prototype.name);

    g_allPrototypes[prototype.name] = prototypePtr;
    g_avatarPrototypes[prototype.name] = prototypePtr;
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

    g_allPrototypes[prototype.name] = prototypePtr;
    g_mountPrototypes[prototype.name] = prototypePtr;
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

    g_allPrototypes[prototype.name] = prototypePtr;
    g_structurePrototypes[prototype.name] = prototypePtr;
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

    g_allPrototypes[prototype.name] = prototypePtr;
    g_objectPrototypes[prototype.name] = prototypePtr;
  }
}


PrototypePtr PrototypesCollection::getPrototype(const PrototypeName& i_name)
{
  return g_allPrototypes.at(i_name);
}

PrototypePtr PrototypesCollection::getAvatarPrototype(const PrototypeName& i_name)
{
  return g_avatarPrototypes.at(i_name);
}

PrototypePtr PrototypesCollection::getMountPrototype(const PrototypeName& i_name)
{
  return g_mountPrototypes.at(i_name);
}

PrototypePtr PrototypesCollection::getStructurePrototype(const PrototypeName& i_name)
{
  return g_structurePrototypes.at(i_name);
}

PrototypePtr PrototypesCollection::getObjectPrototype(const PrototypeName& i_name)
{
  return g_objectPrototypes.at(i_name);
}


const PrototypesMap& PrototypesCollection::getAllPrototypes()
{
  return g_allPrototypes;
}

const PrototypesMap& PrototypesCollection::getAvatarPrototypes()
{
  return g_avatarPrototypes;
}

const PrototypesMap& PrototypesCollection::getMountPrototypes()
{
  return g_mountPrototypes;
}

const PrototypesMap& PrototypesCollection::getStructurePrototypes()
{
  return g_structurePrototypes;
}

const PrototypesMap& PrototypesCollection::getObjectPrototypes()
{
  return g_objectPrototypes;
}
