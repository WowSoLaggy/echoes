#include "stdafx.h"
#include "SessionSaver.h"

#include "Session.h"

#include <LaggySdk/JsonSerializer.h>


void SessionSaver::save(Session& i_session, const fs::path& i_path)
{
  Sdk::JsonSerializer::serialize(i_session, i_path);
}
