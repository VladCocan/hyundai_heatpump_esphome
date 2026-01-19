import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, modbus_controller

DEPENDENCIES = ["modbus_controller"]

# Creează clasa C++ pentru climate
HyundaiHPClimate = cg.esphome_ns.namespace("hyundai_heatpump").class_(
    "HyundaiHPClimate", climate.Climate, cg.Component
)

# Schema ESPHome pentru YAML
CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(HyundaiHPClimate),  # id-ul componenta
    cv.Required("name"): cv.string,
    cv.Required("modbus_controller_id"): cv.use_id(modbus_controller.ModbusController),
}).extend(cv.COMPONENT_SCHEMA)  # extinde schema standard component

async def to_code(config):
    # Creează instanța componentei
    var = cg.new_Pvariable(config[cv.GenerateID()])
    
    # Setează parent-ul modbus
    parent = await cg.get_variable(config["modbus_controller_id"])
    cg.add(var.set_modbus_parent(parent))

    # Înregistrează componenta și climate
    await cg.register_component(var, config)
    await climate.register_climate(var, config)
