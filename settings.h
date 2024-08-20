#pragma once

#include "alarms.h"

#define VALID_FLAG __TIME__

typedef struct {
  char validFlag[8];
  bool is12Hmode;
  Alarm alarms[NUM_ALARMS];
} Settings;

extern Settings settings;

void loadSettings();
void saveSettings();