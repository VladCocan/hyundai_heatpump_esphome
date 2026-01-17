<p align="center">
  <img src="banner.svg" width="100%" />
</p>

<p align="center">
  <img src="logo.svg" width="180" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/ESPHome-Compatible-blue?style=for-the-badge&logo=esphome" />
  <img src="https://img.shields.io/badge/Modbus-RTU-green?style=for-the-badge" />
  <img src="https://img.shields.io/badge/R290-Heatpump-orange?style=for-the-badge" />
  <img src="https://img.shields.io/github/v/release/vlad/hyundai_heatpump_esphome?style=for-the-badge" />
</p>

---

# 🔥 Hyundai R290 Heatpump – ESPHome Custom Component

This project provides a **full ESPHome integration** for **Hyundai / Midea R290 heat pumps** using **Modbus RTU**.  
It exposes a native `climate` entity, sensors, binary sensors, and switches — all automatically discovered by Home Assistant.

The architecture is inspired by the *Samsung HVAC Bus* project but optimized specifically for **R290 monobloc units (1 zone, no DHW)**.

---

# 🚀 Features

- 🔥 Full Modbus RTU control of Hyundai R290 heat pumps  
- 🎛 Native Home Assistant `climate` entity (Heat / Cool / Off)  
- 🎚 Temperature slider **25–75°C**, 1°C step  
- 🌡 20+ sensors automatically exposed  
- ⚙ Bit‑level status decoding (defrost, heating active, pumps, resistors, etc.)  
- 🔌 Switches for Zone 1 and Room Control  
- 📡 ESP32 + RS485 — no proprietary gateway required  
- 🧩 Compatible with ESPHome 2024+  

---

# 📦 Installation

Add this to your ESPHome configuration:

```yaml
external_components:
  - source: github://vlad/hyundai_heatpump_esphome
    components: [hyundai_heatpump]
```

---

# 🛠 Example ESPHome Configuration

```yaml
esphome:
  name: hyundai_r290
  platform: ESP32
  board: esp32dev

wifi:
  ssid: "YOUR_WIFI"
  password: "YOUR_PASSWORD"

logger:
  level: DEBUG

api:
ota:

uart:
  tx_pin: 17
  rx_pin: 16
  baud_rate: 9600

external_components:
  - source: github://vlad/hyundai_heatpump_esphome
    components: [hyundai_heatpump]

climate:
  - platform: hyundai_heatpump
    name: "Hyundai R290"
```

---

# 🧪 Debug / Test Configuration

Create a separate file `debug.yaml`:

```yaml
logger:
  level: DEBUG

interval:
  - interval: 5s
    then:
      - lambda: |-
          ESP_LOGD("HYUNDAI_TEST", "Mode: %u", id(hyundai)->hvac_mode_);
          ESP_LOGD("HYUNDAI_TEST", "T1: %.1f°C", id(hyundai)->current_temp_);
          ESP_LOGD("HYUNDAI_TEST", "T1s: %.1f°C", id(hyundai)->target_temp_);
          ESP_LOGD("HYUNDAI_TEST", "Freq: %.1f Hz", id(hyundai)->compressor_freq_);
```

---

# 🏠 Home Assistant Dashboard Example

```yaml
type: vertical-stack
cards:
  - type: thermostat
    entity: climate.hyundai_r290
    name: Hyundai R290

  - type: entities
    title: Temperatures
    entities:
      - sensor.hyundai_t1
      - sensor.hyundai_tw_in
      - sensor.hyundai_tw_out
      - sensor.hyundai_t3
      - sensor.hyundai_t4
      - sensor.hyundai_t2
      - sensor.hyundai_t2b
      - sensor.hyundai_tl
      - sensor.hyundai_t9i
      - sensor.hyundai_t9o

  - type: entities
    title: Pressures & Compressor
    entities:
      - sensor.hyundai_p1
      - sensor.hyundai_p2
      - sensor.hyundai_freq
      - sensor.hyundai_fan

  - type: entities
    title: Energy & Consumption
    entities:
      - sensor.hyundai_power
      - sensor.hyundai_cop
      - sensor.hyundai_energy
      - sensor.hyundai_voltage
      - sensor.hyundai_current

  - type: entities
    title: Status
    entities:
      - binary_sensor.hyundai_heating_active
      - binary_sensor.hyundai_cooling_active
      - binary_sensor.hyundai_defrost
      - binary_sensor.hyundai_anti_freeze
      - binary_sensor.hyundai_pump_i
      - binary_sensor.hyundai_pump_o

  - type: entities
    title: Control
    entities:
      - switch.hyundai_zone1_power
      - switch.hyundai_room_power
```

---

# 🔧 Hardware Setup

### Required:
- ESP32 (WROOM/WROVER recommended)
- RS485 transceiver (MAX3485 / MAX485)
- 2‑wire Modbus A/B connection
- 5V power for the RS485 module

### Wiring:

| ESP32 | RS485 |
|-------|--------|
| GPIO17 | DI (TX) |
| GPIO16 | RO (RX) |
| 5V | VCC |
| GND | GND |
| A | A+ |
| B | B- |

---

# 📄 License

MIT License

---

# ❤️ Contributing

Pull requests are welcome.  
If you have a different Hyundai/Midea model, feel free to open an issue.

---

# 🧱 Project Status

This component is stable and production‑ready.  
Tested with:

- Hyundai R290 monobloc (1 zone, no DHW)  
- ESP32 WROOM  
- MAX3485 RS485  
