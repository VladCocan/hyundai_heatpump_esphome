import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, modbus_controller
from esphome.const import CONF_NAME

from .const import *

DEPENDENCIES = ["modbus_controller"]

# Creează clasa ESPHome care va genera C++
HyundaiHPClimate = cg.esphome_class(
    "HyundaiHPClimate", climate.Climate, cg.Component
)

CONF_MODBUS_ID = "modbus_controller_id"

# Schema de configurare pentru YAML
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(HyundaiHPClimate),
    cv.Required(CONF_MODBUS_ID): cv.use_id(modbus_controller.ModbusController),
    cv.Optional(CONF_NAME, default="Hyundai Heat Pump"): cv.string,
}).extend(climate._CLIMATE_SCHEMA)  # <--- corect pentru ESPHome 2025+

async def to_code(config):
    # Creează instanța clasei C++
    var = cg.new_Pvariable(config[cv.ID])

    # Leagă componenta ESPHome de ModbusController
    parent = await cg.get_variable(config[CONF_MODBUS_ID])
    cg.add(var.set_modbus_parent(parent))

    # Înregistrează componenta
    await cg.register_component(var, config)
    await climate.register_climate(var, config)
