#pragma once

#define NUM_ALARMS 30

typedef struct {
  uint8_t weekdays : 7;
  uint8_t enabled : 1;
  uint8_t hour;
  uint8_t minute;
} Alarm;

void checkAlarms();