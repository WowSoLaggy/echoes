#include "stdafx.h"
#include "GasTankBehavior.h"

#include "BehaviorAction.h"
#include "Entity.h"
#include "GasPrototypesCollection.h"
#include "Prototypes.h"
#include "Units.h"

#include <LaggyDx/GasPrototype.h>

#include <LaggySdk/StringUtils.h>


namespace
{
  const std::unordered_map<GasTankBehavior::State, std::string> GasTankBehaviorStatesStrings {
    { GasTankBehavior::State::Open, "Open" },
    { GasTankBehavior::State::Closed, "Closed" },
  };

} // anonym NS

DEFINE_ENUM_STR(GasTankBehavior::State, GasTankBehaviorStatesStrings)


GasTankBehavior::GasTankBehavior()
{
}

GasTankBehavior::GasTankBehavior(Entity& i_gasTank)
{
  setGasTank(i_gasTank);
}


void GasTankBehavior::pushFields()
{
  IBehaviorModel::pushFields();

  pushField("state", *((std::int32_t*)&d_state));
  pushObject("unit", d_gasUnit);
}


void GasTankBehavior::update(double i_dt)
{
}


void GasTankBehavior::interact()
{
  switchState();
}


BehaviorModel GasTankBehavior::getModelType() const
{
  return BehaviorModel::GasTank;
}

std::string GasTankBehavior::getDescription() const
{
  const std::string descriptionStr =
    "State: " + StateStr::toString(d_state) + "\n" +
    "Volume: " + std::to_string((int)Units::volumeToLitres(d_gasUnit.getVolume())) + " L\n" +
    "Pressure: " + Sdk::toString(Units::paToKPa(d_gasUnit.getPressure()), 2) + " KPa";

  const auto ratio = getGasesRatio();

  std::string gasesString = "\n";
  for (const auto& [gas, ratio] : ratio)
    gasesString += GasStr::toString(gas) + ": " + Sdk::toString(ratio * 100, 1) + " %\n";

  return descriptionStr + gasesString;
}

BehaviorActions GasTankBehavior::getActions(bool i_devMode)
{
  auto actions = IBehaviorModel::getActions(i_devMode);

  if (i_devMode)
  {
    actions.push_back(std::make_shared<BehaviorAction>("Remove gases",
      [&]() {
        d_gasUnit.clear();
      },
      true));

    actions.push_back(std::make_shared<BehaviorAction>("Fill with oxygen",
      [&]() {
        d_gasUnit.addGas(GasPrototypesCollection::get(Gas::Oxygen).id, 1000000);
      },
      true));
  }

  return actions;
}


Entity& GasTankBehavior::getGasTank() const
{
  return SAFE_DEREF(d_gasTank);
}

void GasTankBehavior::setGasTank(Entity& i_gasTank)
{
  d_gasTank = &i_gasTank;

  if (d_gasTank->hasPrototype())
    d_gasUnit.setVolume(d_gasTank->getPrototype().volume);
}


void GasTankBehavior::open()
{
  if (isOpen())
    return;

  d_state = State::Open;
}

void GasTankBehavior::close()
{
  if (isClose())
    return;

  d_state = State::Closed;
}

void GasTankBehavior::switchState()
{
  if (isOpen())
    close();
  else
    open();
}


bool GasTankBehavior::isOpen() const
{
  return d_state == State::Open;
}

bool GasTankBehavior::isClose() const
{
  return d_state == State::Closed;
}


std::unordered_map<Gas, double> GasTankBehavior::getGasesRatio() const
{
  std::unordered_map<Gas, double> ratio;

  int totalAmount = 0;
  for (const auto& [id, amount] : d_gasUnit.getGases())
  {
    totalAmount += amount;
    ratio[static_cast<Gas>(id)] = amount;
  }

  for (auto& [_, amount] : ratio)
    amount /= totalAmount;

  return ratio;
}
