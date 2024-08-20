#pragma once

#include <DS3231.h>

extern DS3231 rtc;

void initRtc();

extern const String daysOfTheWeek[7];
extern const String monthsOfTheYear[13];
extern const uint8_t daysInMonth[13];