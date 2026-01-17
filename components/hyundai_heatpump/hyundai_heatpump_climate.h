#pragma once

#include "esphome/components/climate/climate.h"
#include "hyundai_heatpump.h"

namespace esphome {
namespace hyundai_heatpump {

class HyundaiHeatpumpClimate : public climate::Climate, public Component {
 public:
  void setup() override;
  void control(const climate::ClimateCall &call) override;
  climate::ClimateTraits traits() override;

  HyundaiHeatpump *parent_{nullptr};
};

}  // namespace hyundai_heatpump
}  // namespace esphome
