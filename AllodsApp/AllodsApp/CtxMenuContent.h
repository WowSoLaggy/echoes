#pragma once

#include "Fwd.h"


class CtxMenuContent
{
public:
  CtxMenuContent(const Entity& i_entity);

  const std::string& getDescription() const;

private:
  std::string d_description;
};
