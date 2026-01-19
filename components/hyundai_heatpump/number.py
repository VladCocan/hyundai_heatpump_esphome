from esphome.components import number, modbus_controller
import esphome.codegen as cg
import esphome.config_validation as cv
from .const import REG_TARGET_TEMP

CONFIG_SCHEMA = number.NUMBER_SCHEMA.extend({
    cv.Required("modbus_controller_id"): cv.use_id(modbus_controller.ModbusController),
}).extend(modbus_controller.MODBUS_ITEM_SCHEMA)

async def to_code(config):
    parent = await cg.get_variable(config["modbus_controller_id"])
    var = cg.new_Pvariable(config[CONF_ID])
    await number.register_number(var, config)
    cg.add(var.set_parent(parent))
    cg.add(var.set_register(REG_TARGET_TEMP))
