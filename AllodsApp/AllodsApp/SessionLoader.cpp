#include "stdafx.h"
#include "SessionLoader.h"

#include "WorldLoader.h"


Session SessionLoader::createNew() const
{
  Session session;

  session.setWorld(std::make_unique<World>(WorldLoader::loadEmpty()));

  return session;
}
