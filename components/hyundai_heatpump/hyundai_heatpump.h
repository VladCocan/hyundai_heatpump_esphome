#pragma once

#include "esphome/components/modbus_controller/modbus_controller.h"
#include "esphome/core/component.h"
#include "register_map_r290.h"

namespace esphome {
namespace hyundai_heatpump {

class HyundaiHeatpump : public Component, public modbus_controller::ModbusDevice {
 public:
  void setup() override;
  void loop() override;

  void set_mode(uint16_t mode);
  void set_t1s(uint16_t temp);
  void set_zone1_power(bool on);
  void set_room_power(bool on);

  float read_float(uint16_t reg);
  uint16_t read_u16(uint16_t reg);

  float current_temp_ = NAN;
  float target_temp_ = NAN;
  uint16_t hvac_mode_ = 0;
  float compressor_freq_ = 0;

  void update_all();

 protected:
  uint32_t last_update_ = 0;
  const uint32_t update_interval_ms_ = 3000;
};

}  // namespace hyundai_heatpump
}  // namespace esphome
