#include "hyundai_heatpump_climate.h"

namespace esphome {
namespace hyundai_heatpump {

void HyundaiHPInternalClimate::setup() {
  // Called once at startup
}

void HyundaiHPInternalClimate::loop() {
  // Poll the hub / update current temperature
  if (!hub_)
    return;

  if (hub_->tw_in_sensor_) {
    this->publish_state(climate::ClimateMode::CLIMATE_MODE_HEAT,
                        hub_->tw_in_sensor_->state);
  }
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
  if (!hub_)
    return;

  if (call.get_target_temperature().has_value()) {
    float temp = *call.get_target_temperature();
    // TODO: Send Modbus command via hub_ to set temperature
  }

  // TODO: add fan/swing control
}

}  // namespace hyundai_heatpump
}  // namespace esphome
