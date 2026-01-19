from esphome.components import switch, modbus_controller
import esphome.codegen as cg
import esphome.config_validation as cv
from .const import *

SWITCHES = {
    "power": REG_POWER,
    "compressor": REG_COMPRESSOR,
    "pump_i": REG_PUMP_I,
    "pump_d": REG_PUMP_D
}

CONFIG_SCHEMA = cv.Schema({
    cv.Required("modbus_controller_id"): cv.use_id(modbus_controller.ModbusController),
    cv.Required("name"): cv.string,
}).extend(modbus_controller.MODBUS_ITEM_SCHEMA)

async def to_code(config):
    parent = await cg.get_variable(config["modbus_controller_id"])
    var = cg.new_Pvariable(config[CONF_ID])
    await switch.register_switch(var, config)
    cg.add(var.set_parent(parent))
    cg.add(var.set_register(SWITCHES[config["name"].lower()]))
