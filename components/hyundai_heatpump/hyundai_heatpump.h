#pragma once
#include "esphome.h"
#include "esphome/components/modbus/modbus.h"

namespace esphome {
namespace hyundai_heatpump {

class HyundaiHPInternalHub : public Component {
 public:
  void set_bus(modbus::Modbus *bus) { this->bus_ = bus; }
 protected:
  modbus::Modbus *bus_;
};

}  // namespace hyundai_heatpump
}  // namespace esphome
