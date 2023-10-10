#include "stdafx.h"
#include "ObjectsView.h"

#include "Object.h"
#include "ObjectView.h"
#include "Prototypes.h"


void ObjectsView::render(const Dx::ISpriteShader& i_shader, const Objects& i_objects) const
{
  ObjectView objectView(i_shader);

  for (const auto objectPtr : i_objects)
  {
    const auto& object = SAFE_DEREF(objectPtr);
    objectView.render(object.getPrototype().texture, object.getPosition(), object.getAnimationPlayer().getCurrentFrame());
  }
}
