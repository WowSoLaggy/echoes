#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"


class ContainerBehavior : public IBehaviorModel
{
public:
  ContainerBehavior(Entity& i_container);

  virtual void interact() override;

  void open();
  void close();
  void switchState();

  bool isOpen();
  bool isClosed();

private:

  enum class State
  {
    Closed,
    Open,
  };

  Entity& d_container;
  State d_state = State::Closed;
};
