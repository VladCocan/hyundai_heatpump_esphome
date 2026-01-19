import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import modbus

DEPENDENCIES = ["modbus"]

CONF_MODBUS_BUS = "modbus_bus"

# Create namespace
hyundai_hp_ns = cg.esphome_ns.namespace("hyundai_heatpump")

# Hub class
HyundaiHPInternalHub = hyundai_hp_ns.class_("HyundaiHPInternalHub", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(HyundaiHPInternalHub),
        cv.Required(CONF_MODBUS_BUS): cv.use_id(modbus.Modbus),
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    bus = await cg.get_variable(config[CONF_MODBUS_BUS])
    cg.add(var.set_bus(bus))
    await cg.register_component(var, config)
