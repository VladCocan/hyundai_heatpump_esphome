#include "hyundai_heatpump_switches.h"
#include "esphome/core/log.h"

namespace esphome {
namespace hyundai_heatpump {

static const char *const TAG = "hyundai_heatpump.switches";

class Zone1PowerSwitch : public switch_::Switch {
 public:
  HyundaiHeatpump *parent_;
  void write_state(bool state) override {
    parent_->set_zone1_power(state);
    publish_state(state);
  }
};

class RoomPowerSwitch : public switch_::Switch {
 public:
  HyundaiHeatpump *parent_;
  void write_state(bool state) override {
    parent_->set_room_power(state);
    publish_state(state);
  }
};

void HyundaiHeatpumpSwitches::setup() {
  ((Zone1PowerSwitch*)zone1_power)->parent_ = parent_;
  ((RoomPowerSwitch*)room_power)->parent_ = parent_;

  ESP_LOGI(TAG, "Hyundai R290 switches initialized");
}

}  // namespace hyundai_heatpump
}  // namespace esphome
