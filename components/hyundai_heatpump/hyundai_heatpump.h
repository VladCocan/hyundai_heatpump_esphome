#pragma once

#include "esphome.h"
#include "esphome/components/modbus/modbus.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/climate/climate.h"

namespace esphome {
namespace hyundai_heatpump {

// -------------------- Hub Class --------------------
class HyundaiHPInternalHub : public Component, public modbus::ModbusDevice {
 public:
  void setup() override {}
  void update() override;

  // Temperature sensors
  sensor::Sensor *tw_in_sensor{nullptr};
  sensor::Sensor *tw_out_sensor{nullptr};
  sensor::Sensor *t1_sensor{nullptr};
  sensor::Sensor *tw2_sensor{nullptr};
  sensor::Sensor *ta_sensor{nullptr};
  sensor::Sensor *t5_sensor{nullptr};
  sensor::Sensor *t4_sensor{nullptr};

  // Binary sensors
  binary_sensor::BinarySensor *compressor{nullptr};
  binary_sensor::BinarySensor *pump_i{nullptr};
  binary_sensor::BinarySensor *pump_d{nullptr};
  binary_sensor::BinarySensor *tbh{nullptr};
  binary_sensor::BinarySensor *ibh1{nullptr};
  binary_sensor::BinarySensor *ibh2{nullptr};

  // Text sensor
  text_sensor::TextSensor *error_code{nullptr};

  // Read registers via Modbus
  float read_register(uint16_t reg);
};

// -------------------- Climate Class --------------------
class HyundaiHPInternalClimate : public climate::Climate {
 public:
  void set_hub(HyundaiHPInternalHub *hub) { this->hub_ = hub; }

  // Required implementations
  climate::ClimateTraits traits() override;
  void control(const climate::ClimateCall &call) override;
  void update() override;

 protected:
  HyundaiHPInternalHub *hub_;
};

}  // namespace hyundai_heatpump
}  // namespace esphome
