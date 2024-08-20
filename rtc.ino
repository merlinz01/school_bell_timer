
#include "buzzer.h"
#include "display.h"
#include "rtc.h"
#include "settings.h"

DS3231 rtc;

void initRtc() {
  rtc.setClockMode(false);
  if (rtc.getYear() > 100) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("No clock module!");
    display.display();
    ring();
    while (1);
  }
}

const String daysOfTheWeek[7] = {"Sun", "Mon", "Tue", "Wed",
                                 "Thu", "Fri", "Sat"};

const String monthsOfTheYear[13] = {"???", "Jan", "Feb", "Mar", "Apr",
                                    "May", "Jun", "Jul", "Aug", "Sep",
                                    "Oct", "Nov", "Dec"};

const uint8_t daysInMonth[13] = {0,  31, 28, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};