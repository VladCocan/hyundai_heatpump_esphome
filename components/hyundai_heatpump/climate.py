import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, modbus_controller
from .const import *

DEPENDENCIES = ["modbus_controller"]

hyundai_ns = cg.esphome_ns.namespace("hyundai_heatpump")
HyundaiHPSensor = hyundai_ns.class_(
    "HyundaiHPSensor", cg.PollingComponent, sensor.Sensor
)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(HyundaiHPSensor),
    cv.Required("modbus_controller_id"): cv.use_id(modbus_controller.ModbusController),
    cv.Optional("name", default="Hyundai Water Temp"): cv.string,
}).extend(sensor._SENSOR_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])  # aici nu mai folosim CONF_ID

    parent = await cg.get_variable(config["modbus_controller_id"])
    cg.add(var.set_modbus_parent(parent))

    await cg.register_component(var, config)
    await sensor.register_sensor(var, config)
