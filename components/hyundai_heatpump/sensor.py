from esphome.components import sensor, modbus_controller
import esphome.codegen as cg
import esphome.config_validation as cv
from .const import *

SENSORS = {
    "water_temp": REG_WATER_TEMP,
    "outdoor_temp": REG_OUTDOOR_TEMP
}

CONFIG_SCHEMA = cv.Schema({
    cv.Required("modbus_controller_id"): cv.use_id(modbus_controller.ModbusController),
    cv.Required("name"): cv.string,
    cv.Optional("register"): cv.uint16_t,
}).extend(modbus_controller.MODBUS_ITEM_SCHEMA)

async def to_code(config):
    parent = await cg.get_variable(config["modbus_controller_id"])
    var = cg.new_Pvariable(config[CONF_ID])
    await sensor.register_sensor(var, config)
    cg.add(var.set_parent(parent))
    register = config.get("register", SENSORS.get(config["name"].lower(), 0x0010))
    cg.add(var.set_register(register))
