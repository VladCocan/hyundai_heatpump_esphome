#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "hyundai_heatpump.h"

namespace esphome {
namespace hyundai_heatpump {

class HyundaiHeatpumpSensors : public Component {
 public:
  HyundaiHeatpump *parent_{nullptr};

  sensor::Sensor *t1_sensor = new sensor::Sensor();
  sensor::Sensor *tw_in_sensor = new sensor::Sensor();
  sensor::Sensor *tw_out_sensor = new sensor::Sensor();
  sensor::Sensor *t3_sensor = new sensor::Sensor();
  sensor::Sensor *t4_sensor = new sensor::Sensor();
  sensor::Sensor *tp_sensor = new sensor::Sensor();
  sensor::Sensor *th_sensor = new sensor::Sensor();
  sensor::Sensor *t2_sensor = new sensor::Sensor();
  sensor::Sensor *t2b_sensor = new sensor::Sensor();
  sensor::Sensor *tl_sensor = new sensor::Sensor();
  sensor::Sensor *t9i_sensor = new sensor::Sensor();
  sensor::Sensor *t9o_sensor = new sensor::Sensor();

  sensor::Sensor *p1_sensor = new sensor::Sensor();
  sensor::Sensor *p2_sensor = new sensor::Sensor();

  sensor::Sensor *freq_sensor = new sensor::Sensor();
  sensor::Sensor *fan_sensor = new sensor::Sensor();

  sensor::Sensor *flow_sensor = new sensor::Sensor();

  sensor::Sensor *current_sensor = new sensor::Sensor();
  sensor::Sensor *voltage_sensor = new sensor::Sensor();
  sensor::Sensor *power_sensor = new sensor::Sensor();
  sensor::Sensor *cop_sensor = new sensor::Sensor();

  sensor::Sensor *energy_sensor = new sensor::Sensor();

  void setup() override {}
  void loop() override;
};

}  // namespace hyundai_heatpump
}  // namespace esphome
