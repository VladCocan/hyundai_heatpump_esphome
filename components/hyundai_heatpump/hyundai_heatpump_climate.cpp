#include "hyundai_heatpump_climate.h"
#include "esphome/core/log.h"

namespace esphome {
namespace hyundai_heatpump {

static const char *const TAG = "hyundai_heatpump.climate";

void HyundaiHeatpumpClimate::setup() {
  ESP_LOGI(TAG, "Hyundai R290 climate entity initialized");
  this->min_temp_ = 25.0f;
  this->max_temp_ = 75.0f;
  this->temp_step_ = 1.0f;
}

void HyundaiHeatpumpClimate::control(const climate::ClimateCall &call) {
  if (this->parent_ == nullptr) return;

  if (call.get_mode().has_value()) {
    auto mode = *call.get_mode();
    switch (mode) {
      case climate::CLIMATE_MODE_OFF: parent_->set_mode(0); break;
      case climate::CLIMATE_MODE_HEAT: parent_->set_mode(3); break;
      case climate::CLIMATE_MODE_COOL: parent_->set_mode(2); break;
      default: ESP_LOGW(TAG, "Unsupported HVAC mode"); break;
    }
    this->mode = mode;
  }

  if (call.get_target_temperature().has_value()) {
    float t = *call.get_target_temperature();
    parent_->set_t1s((uint16_t)t);
    this->target_temperature = t;
  }

  this->publish_state();
}

climate::ClimateTraits HyundaiHeatpumpClimate::traits() {
  climate::ClimateTraits traits;
  traits.set_supported_modes({
      climate::CLIMATE_MODE_OFF,
      climate::CLIMATE_MODE_HEAT,
      climate::CLIMATE_MODE_COOL,
  });
  traits.set_supports_current_temperature(true);
  traits.set_supports_action(true);
  traits.set_visual_min_temperature(25);
  traits.set_visual_max_temperature(75);
  traits.set_visual_temperature_step(1.0f);
  return traits;
}

}  // namespace hyundai_heatpump
}  // namespace esphome
