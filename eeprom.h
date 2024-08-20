#pragma once

#include <SparkFun_External_EEPROM.h>

#define MEMORY_I2C_ADDRESS 0x50

ExternalEEPROM mem;

void initEEPROM();
