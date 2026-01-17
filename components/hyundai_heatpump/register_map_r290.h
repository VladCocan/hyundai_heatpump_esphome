#pragma once

namespace hyundai_r290 {

// CONTROL
static const uint16_t REG_MODE = 1;
static const uint16_t REG_T1S = 11;
static const uint16_t REG_ZONE1_POWER = 16;
static const uint16_t REG_ROOM_POWER = 17;

// TEMPERATURES
static const uint16_t REG_TW_IN = 104;
static const uint16_t REG_TW_OUT = 105;
static const uint16_t REG_T3 = 106;
static const uint16_t REG_T4 = 107;
static const uint16_t REG_TP = 108;
static const uint16_t REG_TH = 109;
static const uint16_t REG_T1 = 110;
static const uint16_t REG_T2 = 112;
static const uint16_t REG_T2B = 113;
static const uint16_t REG_TL = 191;
static const uint16_t REG_T9I = 193;
static const uint16_t REG_T9O = 194;

// PRESSURES
static const uint16_t REG_P1 = 116;
static const uint16_t REG_P2 = 117;

// COMPRESSOR / FAN
static const uint16_t REG_FREQ = 100;
static const uint16_t REG_FAN = 102;

// FLOW
static const uint16_t REG_FLOW = 138;

// ELECTRICAL / ENERGY
static const uint16_t REG_CURRENT = 118;
static const uint16_t REG_VOLTAGE = 119;
static const uint16_t REG_POWER = 150;
static const uint16_t REG_COP = 151;
static const uint16_t REG_ENERGY_HI = 143;
static const uint16_t REG_ENERGY_LO = 144;

// STATUS
static const uint16_t REG_STATUS1 = 128;
static const uint16_t REG_LOAD_OUTPUT = 129;
static const uint16_t REG_STATUS3 = 198;

}  // namespace hyundai_r290
