#pragma once

#include "esphome/core/component.h"
#include "esphome/components/switch/switch.h"
#include "hyundai_heatpump.h"

namespace esphome {
namespace hyundai_heatpump {

class HyundaiHeatpumpSwitches : public Component {
 public:
  HyundaiHeatpump *parent_{nullptr};

  switch_::Switch *zone1_power = new switch_::Switch();
  switch_::Switch *room_power = new switch_::Switch();

  void setup() override;
};

}  // namespace hyundai_heatpump
}  // namespace esphome
