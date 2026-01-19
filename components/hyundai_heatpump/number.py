from esphome.components import number, modbus_controller
import esphome.codegen as cg
import esphome.config_validation as cv
from .const import REG_TARGET_TEMP

CONF_MODBUS_ID = "modbus_controller_id"
CONF_REGISTER = "register"

CONFIG_SCHEMA = number._NUMBER_SCHEMA.extend({
    cv.Required(CONF_MODBUS_ID): cv.use_id(modbus_controller.ModbusController),
    cv.Required("name"): cv.string,
    cv.Optional(CONF_REGISTER, default=REG_TARGET_TEMP): cv.positive_int,
})

async def to_code(config):
    parent = await cg.get_variable(config[CONF_MODBUS_ID])
    var = cg.new_Pvariable(config[CONF_ID])
    await number.register_number(var, config)
    cg.add(var.set_parent(parent))
    cg.add(var.set_register(config[CONF_REGISTER]))
