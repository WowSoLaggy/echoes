#include "stdafx.h"
#include "Fonts.h"


const std::string& Fonts::getMenuFont()
{
  static const std::string font = "agency_fb_20.spritefont";
  return font;
}

const std::string& Fonts::getInGameHintsFont()
{
  static const std::string font = "agency_fb_18.spritefont";
  return font;
}
