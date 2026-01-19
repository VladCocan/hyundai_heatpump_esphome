#include "hyundai_heatpump.h"

namespace esphome {
namespace hyundai_heatpump {

// -------------------- Hub Implementation --------------------
void HyundaiHPInternalHub::update() {
  // Example: read Modbus registers and update sensors
  if (tw_in_sensor) tw_in_sensor->publish_state(read_register(0x0001));
  if (tw_out_sensor) tw_out_sensor->publish_state(read_register(0x0002));
  if (compressor) compressor->publish_state(read_register(0x0100) > 0);
  if (error_code) error_code->publish_state(String(read_register(0x0200), HEX));
}

float HyundaiHPInternalHub::read_register(uint16_t reg) {
  uint16_t value = 0;
  if (this->read_register(reg, &value)) {
    return static_cast<float>(value) / 10.0;  // scale example
  }
  return NAN;
}

// -------------------- Climate Implementation --------------------
climate::ClimateTraits HyundaiHPInternalClimate::traits() {
  auto t = climate::ClimateTraits();
  t.set_supports_current_temperature(true);
  t.set_supports_target_temperature(true);
  t.set_supports_modes(true);
  t.set_supports_fan_mode(false);
  t.set_supports_swing_mode(false);
  return t;
}

void HyundaiHPInternalClimate::control(const climate::ClimateCall &call) {
  if (!hub_) return;
  if (call.get_target_temperature().has_value()) {
    float temp = *call.get_target_temperature();
    hub_->write_register(0x0300, static_cast<uint16_t>(temp * 10));  // write target temp
  }
  if (call.get_mode().has_value()) {
    // Example: heating/cooling mode via Modbus
    hub_->write_register(0x0301, static_cast<uint16_t>(*call.get_mode()));
  }
}

void HyundaiHPInternalClimate::update() {
  // Update climate state from hub
  if (!hub_) return;
  if (this->traits().supports_current_temperature()) {
    this->publish_state();
  }
}

}  // namespace hyundai_heatpump
}  // namespace esphome
