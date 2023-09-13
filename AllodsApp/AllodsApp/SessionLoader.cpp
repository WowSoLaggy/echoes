#include "stdafx.h"
#include "SessionLoader.h"

#include "WorldCreator.h"


Session SessionLoader::createNew() const
{
  Session session;

  session.setWorld(std::make_unique<World>(WorldCreator::createTest()));

  return session;
}
