#pragma once

#include "esphome/core/component.h"
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "hyundai_heatpump.h"

namespace esphome {
namespace hyundai_heatpump {

class HyundaiHeatpumpBinarySensors : public Component {
 public:
  HyundaiHeatpump *parent_{nullptr};

  binary_sensor::BinarySensor *defrost = new binary_sensor::BinarySensor();
  binary_sensor::BinarySensor *anti_freeze = new binary_sensor::BinarySensor();
  binary_sensor::BinarySensor *remote_onoff = new binary_sensor::BinarySensor();
  binary_sensor::BinarySensor *room_ht = new binary_sensor::BinarySensor();
  binary_sensor::BinarySensor *room_cl = new binary_sensor::BinarySensor();

  binary_sensor::BinarySensor *pump_i = new binary_sensor::BinarySensor();
  binary_sensor::BinarySensor *pump_o = new binary_sensor::BinarySensor();
  binary_sensor::BinarySensor *pump_d = new binary_sensor::BinarySensor();
  binary_sensor::BinarySensor *ibh1 = new binary_sensor::BinarySensor();
  binary_sensor::BinarySensor *ibh2 = new binary_sensor::BinarySensor();
  binary_sensor::BinarySensor *tbh = new binary_sensor::BinarySensor();

  binary_sensor::BinarySensor *heating_active = new binary_sensor::BinarySensor();
  binary_sensor::BinarySensor *cooling_active = new binary_sensor::BinarySensor();
  binary_sensor::BinarySensor *dhw_active = new binary_sensor::BinarySensor();

  void setup() override {}
  void loop() override;
};

}  // namespace hyundai_heatpump
}  // namespace esphome
