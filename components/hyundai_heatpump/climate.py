import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, modbus_controller
from .const import *

DEPENDENCIES = ["modbus_controller"]

CONF_MODBUS_ID = "modbus_controller_id"

CONF_ID = "id"  # adaugă asta!

CONFIG_SCHEMA = climate._CLIMATE_SCHEMA.extend({
    cv.Required(CONF_ID): cv.declare_id(climate.Climate),
    cv.Required(CONF_MODBUS_ID): cv.use_id(modbus_controller.ModbusController),
})

HyundaiHP = cg.esphome_ns.class_(
    "HyundaiHP", climate.Climate, cg.Component
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_MODBUS_ID])
    
    
    var = cg.new_Pvariable(config["id"], parent)
    await cg.register_component(var, config)
    await climate.register_climate(var, config)
    cg.add(var.set_modbus_parent(parent))
