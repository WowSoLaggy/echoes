#pragma once


using BehaviorFunction = std::function<void()>;


class BehaviorAction
{
public:
  BehaviorAction(std::string i_name, BehaviorFunction i_function, bool i_devOnly = false);

  const std::string& getName() const;
  bool getDevOnly() const;
  BehaviorFunction getFunction() const;

private:
  std::string d_name;
  bool d_devOnly = false;
  BehaviorFunction d_function;
};
