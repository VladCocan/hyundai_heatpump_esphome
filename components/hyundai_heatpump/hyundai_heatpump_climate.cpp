#include "hyundai_heatpump_climate.h"

namespace esphome {
namespace hyundai_heatpump {

void HyundaiHPInternalClimate::setup() {
  // Called once at startup
}

void HyundaiHPInternalClimate::loop() {
  // Poll the hub / update current temperature
}

climate::ClimateTraits HyundaiHPInternalClimate::traits() {
  auto t = climate::ClimateTraits();
  t.add_feature(climate::CLIMATE_FEATURE_TARGET_TEMPERATURE);
  t.add_feature(climate::CLIMATE_FEATURE_CURRENT_TEMPERATURE);
  t.add_feature(climate::CLIMATE_FEATURE_FAN_MODE);
  t.add_feature(climate::CLIMATE_FEATURE_SWING_MODE);
  return t;
}

void HyundaiHPInternalClimate::control(const climate::ClimateCall &call) {
  // Handle Home Assistant commands (temperature/fan/swing)
  if (call.get_target_temperature().has_value()) {
    float temp = *call.get_target_temperature();
    // Send Modbus command via hub_ to set temperature
  }

  // TODO: add fan/swing control
}

}  // namespace hyundai_heatpump
}  // namespace esphome
