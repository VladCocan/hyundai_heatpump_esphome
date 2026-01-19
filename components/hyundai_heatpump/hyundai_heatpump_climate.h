#pragma once
#include "esphome.h"
#include "esphome/components/climate/climate.h"
#include "hyundai_heatpump.h"

namespace esphome {
namespace hyundai_heatpump {

class HyundaiHPInternalClimate : public climate::Climate, public Component {
 public:
  void set_hub(HyundaiHPInternalHub *hub) { this->hub_ = hub; }
  void set_address(uint8_t address) { this->address_ = address; }

  // Required pure virtual overrides
  climate::ClimateTraits traits() override {
    auto t = climate::ClimateTraits();
    t.set_supports_current_temperature(true);
    return t;
  }
  void control(const climate::ClimateCall &call) override {
    // TODO: implement sending Modbus commands to heat pump
  }

 protected:
  HyundaiHPInternalHub *hub_;
  uint8_t address_;
};

}  // namespace hyundai_heatpump
}  // namespace esphome
