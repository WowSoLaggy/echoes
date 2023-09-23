#pragma once

#include "Session.h"


class SessionLoader
{
public:
  std::unique_ptr<Session> createNew() const;
};
