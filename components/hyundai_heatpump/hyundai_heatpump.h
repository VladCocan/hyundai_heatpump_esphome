#pragma once
#include "esphome.h"
#include "esphome/components/modbus/modbus.h"

class HyundaiHeatPump : public PollingComponent, public modbus::ModbusDevice {
 public:
  // Constructor
  HyundaiHeatPump(uint32_t update_interval_ms = 15000);

  // Climate targets
  void set_zone1_temperature(float temp);
  void set_zone2_temperature(float temp);
  void set_mode(uint8_t mode);  // 1=Auto,2=Cooling,3=Heating

  // DHW
  void set_dhw_temperature(float temp);
  void enable_dhw(bool on);

  // TBH / IBH
  void enable_tbh(bool on);
  void enable_ibh1(bool on);
  void enable_ibh2(bool on);

  // Sensors (ESPHome objects)
  sensor::Sensor *tw_in_sensor_{nullptr};
  sensor::Sensor *tw_out_sensor_{nullptr};
  sensor::Sensor *t1_sensor_{nullptr};
  sensor::Sensor *tw2_sensor_{nullptr};
  sensor::Sensor *ta_sensor_{nullptr};
  sensor::Sensor *t5_sensor_{nullptr};
  sensor::Sensor *t4_sensor_{nullptr};
  binary_sensor::BinarySensor *compressor_{nullptr};
  binary_sensor::BinarySensor *pump_i_{nullptr};
  binary_sensor::BinarySensor *pump_d_{nullptr};
  binary_sensor::BinarySensor *tbh_{nullptr};
  binary_sensor::BinarySensor *ibh1_{nullptr};
  binary_sensor::BinarySensor *ibh2_{nullptr};
  text_sensor::TextSensor *error_code_{nullptr};

  void setup() override;
  void update() override;

 private:
  // Internal helpers
  uint16_t read_register(uint16_t address);
  void write_register(uint16_t address, uint16_t value);
  bool get_bit(uint16_t value, uint8_t bit);

  uint16_t zone1_target_{0};
  uint16_t zone2_target_{0};
  uint16_t dhw_target_{0};
  uint16_t mode_{1};  // Default Auto

  uint16_t last_status_register_{0};
};
