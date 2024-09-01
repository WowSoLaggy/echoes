#pragma once

#include "FreeBaseEntity.h"


class Avatar : public FreeBaseEntity
{
public:
  Avatar();
  Avatar(PrototypePtr i_prototype);

  [[nodiscard]] const AvatarPrototype& getAvatarPrototype() const;

  [[nodiscard]] virtual std::optional<double> getTemperature() const override;
};
