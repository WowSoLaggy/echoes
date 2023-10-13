#include "stdafx.h"
#include "AvatarsView.h"

#include "Avatar.h"
#include "AvatarView.h"
#include "Prototypes.h"


void AvatarsView::render(const Dx::ISpriteShader& i_shader, const Avatars& i_avatars) const
{
  AvatarView avatarView(i_shader);

  for (const auto avatarPtr : i_avatars)
  {
    const auto& avatar = SAFE_DEREF(avatarPtr);
    avatarView.render(avatar.getPrototype().texture, avatar.getPosition(), avatar.getAnimationPlayer().getCurrentFrame());
  }
}
