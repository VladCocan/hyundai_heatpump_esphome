import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, modbus_controller
from .const import *

DEPENDENCIES = ["modbus_controller"]

CONF_MODBUS_ID = "modbus_controller_id"

# Clasa generată în C++
HyundaiHPClimate = cg.global_ns.class_(
    "HyundaiHPClimate", cg.Component, climate.Climate
)

# Schema YAML
CONFIG_SCHEMA = cv.Schema({
    cv.Required(CONF_MODBUS_ID): cv.use_id(modbus_controller.ModbusController),
    cv.GenerateID(): cv.declare_id(HyundaiHPClimate),  # <-- corect
    cv.Optional("name", default="Hyundai Heat Pump"): cv.string,
})

async def to_code(config):
    var = cg.new_Pvariable(config[cv.ID])
    await cg.register_component(var, config)
    await climate.register_climate(var, config)

    # Conectare la ModbusController
    parent = await cg.get_variable(config[CONF_MODBUS_ID])
    cg.add(var.set_modbus_parent(parent))
