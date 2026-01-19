# Modbus Holding Registers – trebuie verificate manual cu service manual Hyundai
REG_POWER = 0x0000          # Pornit/Oprit
REG_MODE = 0x0001           # Mod de funcționare (HEAT/COOL/DHW)
REG_TARGET_TEMP = 0x0002    # Setpoint apă caldă
REG_WATER_TEMP = 0x0010     # Temperatura apei
REG_OUTDOOR_TEMP = 0x0011   # Temperatura exterioară
REG_COMPRESSOR = 0x0020     # Status compresor
REG_PUMP_I = 0x0021         # Status pompa internă
REG_PUMP_D = 0x0022         # Status pompa de distribuție
REG_ERROR = 0x0030          # Cod eroare
