
#include "alarms.h"
#include "alarms_mode.h"
#include "buzzer.h"
#include "display.h"
#include "mode.h"
#include "rtc.h"
#include "settings.h"

uint8_t lastTriggered[NUM_ALARMS];

void checkAlarms() {
  // Disable alarms if we're making changes
  if (current_mode == &alarmsMode) return;
  bool is12h, isPM;
  uint8_t date = rtc.getDate();
  uint8_t dow = (1 << rtc.getDoW());
  uint8_t hour = rtc.getHour(is12h, isPM);
  uint8_t minute = rtc.getMinute();
  for (int i = 0; i < NUM_ALARMS; i++) {
    if (settings.alarms[i].enabled && settings.alarms[i].weekdays & dow &&
        lastTriggered[i] != date && hour == settings.alarms[i].hour &&
        minute == settings.alarms[i].minute) {
      lastTriggered[i] = date;
      alarm(i);
    }
  }
}

void alarm(int alarmIndex) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(16, 10);
  display.print("ALARM ");
  print2DigitNumber(alarmIndex + 1, ' ');
  display.setCursor(16, 40);
  uint8_t hour = settings.alarms[alarmIndex].hour;
  bool is12h, isPM;
  if (settings.is12Hmode) {
    isPM = hour >= 12;
    if (hour == 0) hour = 12;
    if (hour > 12) hour -= 12;
  }
  print2DigitNumber(hour, ' ');
  display.print(':');
  print2DigitNumber(settings.alarms[alarmIndex].minute, '0');
  display.print(settings.is12Hmode ? (isPM ? " PM" : " AM") : "");
  display.display();
  ring();
  current_mode->refreshDisplay();
}
