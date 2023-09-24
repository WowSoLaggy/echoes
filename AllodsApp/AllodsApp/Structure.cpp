#include "stdafx.h"
#include "Structure.h"


Structure::Structure(const StructurePrototype& i_prototype)
  : d_prototype(i_prototype)
{
}


void Structure::update(const double i_dt)
{
  d_animationPlayer.update(i_dt);
}


const StructurePrototype& Structure::getPrototype() const
{
  return d_prototype;
}


Dx::Animation2Player& Structure::getAnimationPlayer()
{
  return d_animationPlayer;
}

const Dx::Animation2Player& Structure::getAnimationPlayer() const
{
  return d_animationPlayer;
}
