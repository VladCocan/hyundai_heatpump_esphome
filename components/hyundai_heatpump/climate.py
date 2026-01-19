import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, modbus_controller
from esphome.const import CONF_NAME

from .const import *

DEPENDENCIES = ["modbus_controller"]

CONF_MODBUS_ID = "modbus_controller_id"

# Creează namespace-ul ESPHome pentru componenta ta
hyundai_ns = cg.esphome_ns.namespace("hyundai_heatpump")

# Creează clasa Python care va fi generată în C++
HyundaiHPClimate = hyundai_ns.class_(
    "HyundaiHPClimate", climate.Climate, cg.Component
)

# Schema YAML
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(HyundaiHPClimate),  # aici se generează ID
    cv.Required(CONF_MODBUS_ID): cv.use_id(modbus_controller.ModbusController),
    cv.Optional(CONF_NAME, default="Hyundai Heat Pump"): cv.string,
}).extend(climate._CLIMATE_SCHEMA)

async def to_code(config):
    # Folosește ID-ul generat de cv.GenerateID()
    var = cg.new_Pvariable(config[cv.GenerateID()])  # NU mai folosi cv.ID

    # Conectează la modbus_controller
    parent = await cg.get_variable(config[CONF_MODBUS_ID])
    cg.add(var.set_modbus_parent(parent))

    # Înregistrează componenta ESPHome
    await cg.register_component(var, config)
    await climate.register_climate(var, config)
