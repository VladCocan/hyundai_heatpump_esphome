#include "hyundai_heatpump_sensors.h"
#include "register_map_r290.h"

namespace esphome {
namespace hyundai_heatpump {

void HyundaiHeatpumpSensors::loop() {
  if (!parent_) return;

  t1_sensor->publish_state(parent_->read_float(hyundai_r290::REG_T1));
  tw_in_sensor->publish_state(parent_->read_float(hyundai_r290::REG_TW_IN));
  tw_out_sensor->publish_state(parent_->read_float(hyundai_r290::REG_TW_OUT));
  t3_sensor->publish_state(parent_->read_float(hyundai_r290::REG_T3));
  t4_sensor->publish_state(parent_->read_float(hyundai_r290::REG_T4));
  tp_sensor->publish_state(parent_->read_float(hyundai_r290::REG_TP));
  th_sensor->publish_state(parent_->read_float(hyundai_r290::REG_TH));
  t2_sensor->publish_state(parent_->read_float(hyundai_r290::REG_T2));
  t2b_sensor->publish_state(parent_->read_float(hyundai_r290::REG_T2B));
  tl_sensor->publish_state(parent_->read_float(hyundai_r290::REG_TL));

  float t9i_raw = parent_->read_float(hyundai_r290::REG_T9I);
  float t9o_raw = parent_->read_float(hyundai_r290::REG_T9O);
  t9i_sensor->publish_state(t9i_raw == 0x7fff ? NAN : t9i_raw * 0.1f);
  t9o_sensor->publish_state(t9o_raw == 0x7fff ? NAN : t9o_raw * 0.1f);

  p1_sensor->publish_state(parent_->read_float(hyundai_r290::REG_P1));
  p2_sensor->publish_state(parent_->read_float(hyundai_r290::REG_P2));

  freq_sensor->publish_state(parent_->read_float(hyundai_r290::REG_FREQ));
  fan_sensor->publish_state(parent_->read_float(hyundai_r290::REG_FAN));

  flow_sensor->publish_state(parent_->read_float(hyundai_r290::REG_FLOW) * 0.01f);

  current_sensor->publish_state(parent_->read_float(hyundai_r290::REG_CURRENT));
  voltage_sensor->publish_state(parent_->read_float(hyundai_r290::REG_VOLTAGE));
  power_sensor->publish_state(parent_->read_float(hyundai_r290::REG_POWER) * 0.01f);
  cop_sensor->publish_state(parent_->read_float(hyundai_r290::REG_COP) * 0.01f);

  uint32_t hi = parent_->read_u16(hyundai_r290::REG_ENERGY_HI);
  uint32_t lo = parent_->read_u16(hyundai_r290::REG_ENERGY_LO);
  energy_sensor->publish_state((hi << 16) | lo);
}

}  // namespace hyundai_heatpump
}  // namespace esphome
