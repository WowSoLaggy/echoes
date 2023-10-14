#include "stdafx.h"
#include "SessionSaver.h"

#include <LaggySdk/json.h>
#include <LaggySdk/JsonHelper.h>


void SessionSaver::save(const Session& i_session, const fs::path& i_path)
{
  Json::Value root;

  root["session"] = 42;

  Sdk::JsonHelper::save(root, i_path);
}
