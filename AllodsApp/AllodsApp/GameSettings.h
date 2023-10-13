#pragma once

#include <LaggyDx/AppSettings.h>


struct GameSettings : public Dx::AppSettings
{
  fs::path savesPath = "Saves";
};
