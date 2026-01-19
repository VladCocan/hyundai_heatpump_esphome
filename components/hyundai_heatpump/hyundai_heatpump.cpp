#include "hyundai_heatpump.h"

namespace esphome {
namespace hyundai_heatpump {

void HyundaiHPInternalHub::setup() {
  // Initialize sensors, binary sensors, modbus reads here
}

void HyundaiHPInternalHub::update() {
  // Periodic updates: read modbus registers, update sensors
}

climate::ClimateTraits HyundaiHPInternalClimate::traits() {
  climate::ClimateTraits t;
  t.set_supports_current_temperature(true);
  t.set_supports_target_temperature(true);
  t.supports_modes = true;
  t.supports_fan_modes = true;
  t.supports_swing_modes = true;
  return t;
}

void HyundaiHPInternalClimate::control(const ClimateCall &call) {
  // Send commands to the hub via hub_->modbus_bus_
}

void HyundaiHPInternalClimate::update() {
  // Read current temperature from hub and publish state
  if (!hub_)
    return;
  this->publish_state(climate::ClimateMode::CLIMATE_MODE_HEAT, hub_->tw_in_sensor_->state);
}

}  // namespace hyundai_heatpump
}  // namespace esphome
