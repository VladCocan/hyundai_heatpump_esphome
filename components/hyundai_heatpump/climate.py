import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, modbus_controller

DEPENDENCIES = ["modbus_controller"]

# Declari clasa ta Python care va genera C++
HyundaiHPClimate = cg.esphome_ns.namespace("hyundai_heatpump").class_(
    "HyundaiHPClimate", climate.Climate, cg.Component
)

# Schema de configurare (ESPHome 2025+)
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(HyundaiHPClimate),  # id-ul pentru componenta ta
    cv.Required("modbus_controller_id"): cv.use_id(modbus_controller.ModbusController),
    cv.Required("name"): cv.string,
}).extend(climate.CLIMATE_SCHEMA)

async def to_code(config):
    # creează variabila C++
    var = cg.new_Pvariable(config[cv.GenerateID()])
    await cg.register_component(var, config)
    await climate.register_climate(var, config)

    # legătura cu modbus_controller
    parent = await cg.get_variable(config["modbus_controller_id"])
    cg.add(var.set_modbus_parent(parent))
