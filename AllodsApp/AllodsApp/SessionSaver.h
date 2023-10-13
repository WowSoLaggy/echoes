#pragma once

#include "Fwd.h"


class SessionSaver
{
public:
  static void save(const Session& i_session, const fs::path& i_path);

private:
  SessionSaver() = delete;
};
