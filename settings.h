#pragma once

#include "alarms.h"

#define SETTINGS_ADDRESS 0x10
#define VALID_FLAG 96

typedef struct {
  char validFlag;
  bool is12Hmode;
  Alarm alarms[NUM_ALARMS];
} Settings;

extern Settings settings;

void loadSettings();
void saveSettings();