
#include "alarms.h"
#include "buzzer.h"
#include "display.h"
#include "menu_mode.h"
#include "rtc.h"
#include "settings.h"
#include "time_display_mode.h"

void TimeDisplayMode::displayMode() {
  display.setTextSize(3);
  display.setCursor(8, 4);
  bool is12h, isPM;
  uint8_t hour = rtc.getHour(is12h, isPM);
  is12h = settings.is12Hmode;
  if (is12h) {
    isPM = hour >= 12;
    if (hour == 0) hour = 12;
    if (hour > 12) hour -= 12;
  }
  print2DigitNumber(hour, ' ');

  uint8_t second = rtc.getSecond();
  display.print((second % 2 == 0) ? ':' : ' ');

  uint8_t minute = rtc.getMinute();
  print2DigitNumber(minute, '0');

  display.setTextSize(1);
  display.setCursor(100, 4);
  display.print(':');
  print2DigitNumber(second, '0');

  display.setCursor(104, 18);
  if (is12h) {
    display.print(isPM ? "PM" : "AM");
  } else {
    display.print("24h");
  }

  display.drawFastHLine(5, 30, 118, WHITE);

  display.setTextSize(2);
  display.setCursor(5, 36);
  display.print(daysOfTheWeek[rtc.getDoW()]);
  display.print(' ');
  bool century;
  display.print(monthsOfTheYear[rtc.getMonth(century)]);
  display.print(' ');
  display.print(rtc.getDate());

  display.setCursor(97, 55);
  display.setTextSize(1);
  display.print(' ');
  display.print(2000 + rtc.getYear());

  display.setCursor(3, 55);
  print2DigitNumber(rtc.getTemperature() * 9 / 5 + 32, ' ');
  display.print(" F");
  display.drawCircle(17, 56, 1, WHITE);

  display.drawRect(0, 0, 128, 64, WHITE);
}

void TimeDisplayMode::init() { lastSecond = -1; }

void TimeDisplayMode::ok() { ring(); }

void TimeDisplayMode::cancel() { setMode(&menuMode); }

void TimeDisplayMode::plus() { this->refreshDisplay(); }

void TimeDisplayMode::minus() { this->refreshDisplay(); }

void TimeDisplayMode::loop() {
  int second = rtc.getSecond();
  if (second != lastSecond) {
    lastSecond = second;
    this->refreshDisplay();
  }
}

TimeDisplayMode timeDisplayMode;
