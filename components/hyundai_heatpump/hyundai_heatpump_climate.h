#pragma once

#include "esphome/core/component.h"
#include "esphome/components/climate/climate.h"
#include "esphome/components/sensor/sensor.h"
#include "hyundai_heatpump.h"  // for HyundaiHPInternalHub

namespace esphome {
namespace hyundai_heatpump {

class HyundaiHPInternalClimate : public climate::Climate {
 public:
  void setup() override;
  void loop() override;
  climate::ClimateTraits traits() override;
  void control(const climate::ClimateCall &call) override;

  void set_hub(HyundaiHPInternalHub *hub) { hub_ = hub; }

 protected:
  HyundaiHPInternalHub *hub_{nullptr};
};

}  // namespace hyundai_heatpump
}  // namespace esphome
