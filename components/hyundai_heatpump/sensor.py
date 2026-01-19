from esphome.components import sensor, modbus_controller
import esphome.codegen as cg
import esphome.config_validation as cv
from .const import *

CONF_MODBUS_ID = "modbus_controller_id"
CONF_REGISTER = "register"

CONFIG_SCHEMA = cv.Schema({
    cv.Required(CONF_MODBUS_ID): cv.use_id(modbus_controller.ModbusController),
    cv.Required("name"): cv.string,
    cv.Required(CONF_REGISTER): cv.positive_int,
})

async def to_code(config):
    parent = await cg.get_variable(config[CONF_MODBUS_ID])
    var = cg.new_Pvariable(config[CONF_ID])
    await sensor.register_sensor(var, config)
    cg.add(var.set_parent(parent))
    cg.add(var.set_register(config[CONF_REGISTER]))
