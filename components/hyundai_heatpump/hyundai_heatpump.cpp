#include "hyundai_heatpump.h"

HyundaiHeatPump::HyundaiHeatPump(uint32_t update_interval_ms)
  : PollingComponent(update_interval_ms) {}

// Bit helper
bool HyundaiHeatPump::get_bit(uint16_t value, uint8_t bit) {
  return (value >> bit) & 1;
}

// Modbus read
uint16_t HyundaiHeatPump::read_register(uint16_t address) {
  uint16_t value;
  if (!this->modbus_read_holding_registers(address - 40001, 1, &value)) {
    ESP_LOGW("HyundaiHeatPump", "Failed to read register %u", address);
    return 0xFFFF;
  }
  return value;
}

// Modbus write
void HyundaiHeatPump::write_register(uint16_t address, uint16_t value) {
  if (!this->modbus_write_single_register(address - 40001, value)) {
    ESP_LOGW("HyundaiHeatPump", "Failed to write register %u", address);
  }
}

// Setup
void HyundaiHeatPump::setup() {
  ESP_LOGCONFIG("HyundaiHeatPump", "Component setup done");
}

// Setters
void HyundaiHeatPump::set_zone1_temperature(float temp) {
  zone1_target_ = static_cast<uint16_t>(temp * 10);
  write_register(40003, zone1_target_);
}

void HyundaiHeatPump::set_zone2_temperature(float temp) {
  zone2_target_ = static_cast<uint16_t>(temp * 10);
  write_register(40005, zone2_target_);
}

void HyundaiHeatPump::set_mode(uint8_t mode) {
  mode_ = mode;
  write_register(40002, mode_);
}

void HyundaiHeatPump::set_dhw_temperature(float temp) {
  dhw_target_ = static_cast<uint16_t>(temp * 10);
  write_register(40010, dhw_target_);
}

void HyundaiHeatPump::enable_dhw(bool on) {
  uint16_t reg = read_register(40001);
  if (reg == 0xFFFF) return;
  if (on) reg |= (1 << 1); else reg &= ~(1 << 1);
  write_register(40001, reg);
}

void HyundaiHeatPump::enable_tbh(bool on) {
  uint16_t reg = read_register(40001);
  if (reg == 0xFFFF) return;
  if (on) reg |= (1 << 3); else reg &= ~(1 << 3);
  write_register(40001, reg);
}

void HyundaiHeatPump::enable_ibh1(bool on) {
  uint16_t reg = read_register(40001);
  if (reg == 0xFFFF) return;
  if (on) reg |= (1 << 2); else reg &= ~(1 << 2);
  write_register(40001, reg);
}

void HyundaiHeatPump::enable_ibh2(bool on) {
  uint16_t reg = read_register(40001);
  if (reg == 0xFFFF) return;
  if (on) reg |= (1 << 4); else reg &= ~(1 << 4);
  write_register(40001, reg);
}

// Polling update
void HyundaiHeatPump::update() {
  // Temperatures
  uint16_t tw_in = read_register(40103);
  if (tw_in != 0xFFFF && tw_in_sensor_) tw_in_sensor_->publish_state(tw_in / 10.0f);

  uint16_t tw_out = read_register(40104);
  if (tw_out != 0xFFFF && tw_out_sensor_) tw_out_sensor_->publish_state(tw_out / 10.0f);

  uint16_t t1 = read_register(40111);
  if (t1 != 0xFFFF && t1_sensor_) t1_sensor_->publish_state(t1 / 10.0f);

  uint16_t tw2 = read_register(40112);
  if (tw2 != 0xFFFF && tw2_sensor_) tw2_sensor_->publish_state(tw2 / 10.0f);

  uint16_t ta = read_register(40114);
  if (ta != 0xFFFF && ta_sensor_) ta_sensor_->publish_state(ta / 10.0f);

  uint16_t t5 = read_register(40115);
  if (t5 != 0xFFFF && t5_sensor_) t5_sensor_->publish_state(t5 / 10.0f);

  uint16_t t4 = read_register(40109);
  if (t4 != 0xFFFF && t4_sensor_) t4_sensor_->publish_state(t4 / 10.0f);

  // Status bits
  uint16_t status = read_register(40129);
  if (status != 0xFFFF) {
    if (compressor_) compressor_->publish_state(get_bit(status, 0));
    if (pump_i_) pump_i_->publish_state(get_bit(status, 3));
    if (pump_d_) pump_d_->publish_state(get_bit(status, 2));
    if (tbh_) tbh_->publish_state(get_bit(status, 0));
    if (ibh1_) ibh1_->publish_state(get_bit(status, 0));
    if (ibh2_) ibh2_->publish_state(get_bit(status, 1));
  }

  // Error code
  uint16_t error = read_register(40188);
  if (error != 0xFFFF && error_code_) {
    char buf[16];
    sprintf(buf, "0x%04X", error);
    error_code_->publish_state(buf);
  }
}
