#include "hyundai_heatpump.h"
#include "esphome/core/log.h"

namespace esphome {
namespace hyundai_heatpump {

static const char *const TAG = "hyundai_heatpump";

void HyundaiHeatpump::setup() {
  ESP_LOGI(TAG, "Hyundai R290 driver initialized");
}

void HyundaiHeatpump::loop() {
  const uint32_t now = millis();
  if (now - last_update_ > update_interval_ms_) {
    last_update_ = now;
    update_all();
  }
}

void HyundaiHeatpump::set_mode(uint16_t mode) {
  ESP_LOGI(TAG, "Setting mode = %u", mode);
  this->write_single_register(hyundai_r290::REG_MODE, mode);
  hvac_mode_ = mode;
}

void HyundaiHeatpump::set_t1s(uint16_t temp) {
  ESP_LOGI(TAG, "Setting T1s = %u °C", temp);
  this->write_single_register(hyundai_r290::REG_T1S, temp);
  target_temp_ = temp;
}

void HyundaiHeatpump::set_zone1_power(bool on) {
  ESP_LOGI(TAG, "Zone1 power = %s", on ? "ON" : "OFF");
  this->write_single_register(hyundai_r290::REG_ZONE1_POWER, on ? 1 : 0);
}

void HyundaiHeatpump::set_room_power(bool on) {
  ESP_LOGI(TAG, "Room power = %s", on ? "ON" : "OFF");
  this->write_single_register(hyundai_r290::REG_ROOM_POWER, on ? 1 : 0);
}

float HyundaiHeatpump::read_float(uint16_t reg) {
  uint16_t raw;
  if (!this->read_holding_register(reg, &raw)) {
    ESP_LOGW(TAG, "Failed to read register %u", reg);
    return NAN;
  }
  return static_cast<float>(raw);
}

uint16_t HyundaiHeatpump::read_u16(uint16_t reg) {
  uint16_t raw;
  if (!this->read_holding_register(reg, &raw)) {
    ESP_LOGW(TAG, "Failed to read register %u", reg);
    return 0;
  }
  return raw;
}

void HyundaiHeatpump::update_all() {
  current_temp_ = read_float(hyundai_r290::REG_T1);
  target_temp_ = read_float(hyundai_r290::REG_T1S);
  hvac_mode_ = read_u16(hyundai_r290::REG_MODE);
  compressor_freq_ = read_float(hyundai_r290::REG_FREQ);

  ESP_LOGD(TAG, "T1=%.1f°C, T1s=%.1f°C, mode=%u, freq=%.1f Hz",
           current_temp_, target_temp_, hvac_mode_, compressor_freq_);
}

}  // namespace hyundai_heatpump
}  // namespace esphome
