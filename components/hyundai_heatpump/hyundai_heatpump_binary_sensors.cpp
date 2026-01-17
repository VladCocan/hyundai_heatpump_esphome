#include "hyundai_heatpump_binary_sensors.h"
#include "register_map_r290.h"

namespace esphome {
namespace hyundai_heatpump {

void HyundaiHeatpumpBinarySensors::loop() {
  if (!parent_) return;

  uint16_t s1 = parent_->read_u16(hyundai_r290::REG_STATUS1);
  uint16_t lo = parent_->read_u16(hyundai_r290::REG_LOAD_OUTPUT);
  uint16_t s3 = parent_->read_u16(hyundai_r290::REG_STATUS3);

  defrost->publish_state(s1 & 0b10);
  anti_freeze->publish_state(s1 & 0b100);
  remote_onoff->publish_state(s1 & 0b10000);
  room_ht->publish_state(s1 & 0b1000000);
  room_cl->publish_state(s1 & 0b10000000);

  pump_i->publish_state(lo & 0b1000);
  pump_o->publish_state(lo & 0b1000000);
  pump_d->publish_state(lo & 0b10000000);

  ibh1->publish_state(lo & 0b1);
  ibh2->publish_state(lo & 0b10);
  tbh->publish_state(lo & 0b100);

  heating_active->publish_state(s3 & 0b10000);
  cooling_active->publish_state(s3 & 0b1000);
  dhw_active->publish_state(s3 & 0b100000);
}

}  // namespace hyundai_heatpump
}  // namespace esphome
