#include "stdafx.h"
#include "SessionLoader.h"

#include "WorldCreator.h"


std::unique_ptr<Session> SessionLoader::createNew() const
{
  auto session = std::make_unique<Session>();

  session->setWorld(WorldCreator::createTest());

  return session;
}
