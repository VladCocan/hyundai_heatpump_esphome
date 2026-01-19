#pragma once

#include "esphome.h"
#include "esphome/components/modbus/modbus.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/climate/climate.h"


namespace esphome {
namespace hyundai_heatpump {

class HyundaiHPInternalHub : public Component, public PollingComponent {
 public:
  HyundaiHPInternalHub(Modbus *modbus_bus) : modbus_bus_(modbus_bus) {}

  void setup() override;
  void update() override;

  // Sensors
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

  Modbus *modbus_bus_{nullptr};
};

class HyundaiHPInternalClimate : public climate::Climate {
 public:
  void set_hub(HyundaiHPInternalHub *hub) { this->hub_ = hub; }

  ClimateTraits traits() override;
  void control(const ClimateCall &call) override;
  void update() override;

 protected:
  HyundaiHPInternalHub *hub_{nullptr};
};

}  // namespace hyundai_heatpump
}  // namespace esphome
