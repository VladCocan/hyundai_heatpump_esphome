import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate, modbus_controller

DEPENDENCIES = ["modbus_controller"]

hyundai_ns = cg.esphome_ns.namespace("hyundai_heatpump")

HyundaiHPClimate = hyundai_ns.class_(
    "HyundaiHPClimate",
    climate.Climate,
    cg.Component,
)

CONFIG_SCHEMA = climate.CLIMATE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(HyundaiHPClimate),
        cv.Required("modbus_controller_id"): cv.use_id(
            modbus_controller.ModbusController
        ),
    }
)

async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])

    parent = await cg.get_variable(config["modbus_controller_id"])
    cg.add(var.set_modbus_parent(parent))

    await cg.register_component(var, config)
    await climate.register_climate(var, config)
