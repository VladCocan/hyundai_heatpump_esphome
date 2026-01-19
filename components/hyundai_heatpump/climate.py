import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import climate

from . import HyundaiHPInternalHub

DEPENDENCIES = ["hyundai_heatpump"]

CONF_ADDRESS = "address"
CONF_HUB = "modbus_bus"

hyundai_hp_ns = cg.esphome_ns.namespace("hyundai_heatpump")

# Climate class
HyundaiHPInternalClimate = hyundai_hp_ns.class_(
    "HyundaiHPInternalClimate", climate.Climate, cg.Component
)

# 2025+ uses _CLIMATE_SCHEMA
CONFIG_SCHEMA = climate._CLIMATE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(HyundaiHPInternalClimate),
        cv.Required(CONF_HUB): cv.use_id(HyundaiHPInternalHub),
        cv.Required(CONF_ADDRESS): cv.int_range(min=1, max=247),
    }
)


async def to_code(config):
    hub = await cg.get_variable(config[CONF_HUB])
    var = cg.new_Pvariable(config[cv.GenerateID()])
    cg.add(var.set_hub(hub))
    cg.add(var.set_address(config[CONF_ADDRESS]))
    await climate.register_climate(var, config)
