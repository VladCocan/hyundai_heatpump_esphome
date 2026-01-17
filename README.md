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

Integrare completă pentru pompele de căldură **Hyundai / Midea R290** prin **Modbus RTU**, cu suport nativ pentru:

- entitate `climate`
- senzori
- binary_sensors
- switch-uri
- control complet al temperaturii și modurilor

Componentul este inspirat de arhitectura *Samsung HVAC Bus*, dar optimizat pentru R290, 1 zonă, fără DHW.

---

# 🚀 Caracteristici

- 🔥 Control complet al pompei Hyundai R290 prin Modbus RTU  
- 🎛 Climate nativ în Home Assistant (Heat / Cool / Off)  
- 🎚 Slider temperatură **25–75°C**, pas **1°C**  
- 🌡 20+ senzori integrați automat  
- ⚙ Statusuri pe biți (defrost, heating active, pumps etc.)  
- 🔌 Switch-uri pentru Zone 1 și Room Control  
- 📡 ESP32 + RS485, fără gateway-uri comerciale  
- 🧩 Compatibil ESPHome 2024+  

---

# 📦 Instalare

Adaugă în fișierul tău ESPHome:

```yaml
external_components:
  - source: github://vlad/hyundai_heatpump_esphome
    components: [hyundai_heatpump]
```

---

# 🛠 Exemplu complet de configurare ESPHome

```yaml
esphome:
  name: hyundai_r290
  platform: ESP32
  board: esp32dev

wifi:
  ssid: "WIFI_TAU"
  password: "PAROLA_TA"

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

# 🧪 Debug / Test

Creează un fișier separat `debug.yaml`:

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

# 🏠 Dashboard Lovelace (Home Assistant)

```yaml
type: vertical-stack
cards:
  - type: thermostat
    entity: climate.hyundai_r290
    name: Hyundai R290

  - type: entities
    title: Temperaturi
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
    title: Presiuni & Compresor
    entities:
      - sensor.hyundai_p1
      - sensor.hyundai_p2
      - sensor.hyundai_freq
      - sensor.hyundai_fan

  - type: entities
    title: Energie & Consum
    entities:
      - sensor.hyundai_power
      - sensor.hyundai_cop
      - sensor.hyundai_energy
      - sensor.hyundai_voltage
      - sensor.hyundai_current

  - type: entities
    title: Statusuri
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

### Necesare:
- ESP32 (WROOM/WROVER recomandat)
- Convertor RS485 (MAX3485 / MAX485)
- 2 fire pentru Modbus A/B
- Alimentare 5V pentru convertor

### Conexiuni:

| ESP32 | RS485 |
|-------|--------|
| GPIO17 | DI (TX) |
| GPIO16 | RO (RX) |
| 5V | VCC |
| GND | GND |
| A | A+ |
| B | B- |

---

# 📄 Licență

MIT License

---

# ❤️ Contribuții

Pull request‑urile sunt binevenite.  
Dacă ai un alt model Hyundai/Midea, deschide un issue pentru suport.

---

# 🧱 Status proiect

Acest component este stabil și pregătit pentru producție.  
Testat pe:

- Hyundai R290 monobloc (1 zonă, fără DHW)
- ESP32 WROOM
- MAX3485 RS485
