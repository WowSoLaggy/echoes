#pragma once


class Fonts
{
public:
  static const std::string& getMenuFont();
  static const std::string& getInGameHintsFont();

private:
  Fonts() = delete;
};
