#include "stdafx.h"
#include "SessionLoader.h"

#include "LocationCreator.h"


std::unique_ptr<Session> SessionLoader::createNew() const
{
  auto session = std::make_unique<Session>();

  session->setLocation(LocationCreator::createTest());

  return session;
}
