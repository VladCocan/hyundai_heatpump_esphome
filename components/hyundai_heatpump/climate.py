# climate.py
import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, modbus_controller
from .const import *

DEPENDENCIES = ["modbus_controller"]

CONF_MODBUS_ID = "modbus_controller_id"

# Declari ID-ul pentru YAML
CONFIG_SCHEMA = climate.CLIMATE_SCHEMA.extend({
    cv.Required(CONF_MODBUS_ID): cv.use_id(modbus_controller.ModbusController),
}).extend({
    cv.GenerateID(): cv.declare_id()  # permite `id:` în YAML
})

# Clasa Python -> ESPHome va genera C++ automat
HyundaiHPClimate = cg.global_ns.class_(
    "HyundaiHPClimate", cg.Component, climate.Climate
)

async def to_code(config):
    # Creează variabila componentă
    var = cg.new_Pvariable(config[cv.ID])
    await cg.register_component(var, config)
    await climate.register_climate(var, config)

    # Conectează modulul Modbus
    parent = await cg.get_variable(config[CONF_MODBUS_ID])
    cg.add(var.set_modbus_parent(parent))

# Metodele clasei care vor fi generate în C++
cg.add_define(HyundaiHPClimate.setup)
cg.add_define(HyundaiHPClimate.loop)
cg.add_define(HyundaiHPClimate.traits)
cg.add_define(HyundaiHPClimate.control)
cg.add_define(HyundaiHPClimate.update)
