#include "stdafx.h"
#include "ObjectsView.h"

#include "Object.h"
#include "Prototypes.h"

#include <LaggyDx/AnimatedSprite.h>
#include <LaggyDx/ISpriteShader.h>


void ObjectsView::render(const Dx::ISpriteShader& i_shader, const Objects& i_objects) const
{
  Dx::AnimatedSprite sprite;

  for (const auto objectPtr : i_objects)
  {
    const auto& object = SAFE_DEREF(objectPtr);

    sprite.setTexture(object.getPrototype().texture);
    sprite.setCurrentFrame(object.getAnimationPlayer().getCurrentFrame());
    sprite.resetSizeToTexture();

    const auto pos = object.getPosition() - object.getSize() / 2;
    sprite.setPosition(pos);

    i_shader.draw(sprite);
  }
}
