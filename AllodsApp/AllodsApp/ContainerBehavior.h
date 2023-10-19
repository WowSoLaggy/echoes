#pragma once

#include "Fwd.h"
#include "IBehaviorModel.h"


class ContainerBehavior : public IBehaviorModel
{
public:
  ContainerBehavior();
  ContainerBehavior(Entity* i_container);

  virtual void pushFields() override;
  virtual void interact() override;

  virtual BehaviorModel getModelType() const override;

  void setContainer(Entity* i_container);

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

  Entity* d_container = nullptr;
  State d_state = State::Closed;

  Entity& getContainer() const;
};
