
#include "display.h"
#include "menu_mode.h"
#include "mode.h"
#include "rtc.h"
#include "set_time_mode.h"
#include "settings.h"

void SetTimeMode::init() {
  this->selectedField = 0;
  this->editing = false;
}

void SetTimeMode::displayMode() {
  display.setTextSize(2);
  display.setCursor(15, 3);
  display.println("Set time");

  display.setCursor(20, 21);
  bool is12h, isPM;
  uint8_t hour = rtc.getHour(is12h, isPM);
  is12h = settings.is12Hmode;
  if (is12h) {
    isPM = hour >= 12;
    if (hour == 0) hour = 12;
    if (hour > 12) hour -= 12;
  }
  print2DigitNumber(hour, ' ');
  display.print(':');
  int minute = rtc.getMinute();
  print2DigitNumber(minute, '0');
  display.setTextSize(1);
  display.print(' ');
  display.println(is12h ? (isPM ? "PM" : "AM") : "");

  display.setTextSize(1);
  display.setCursor(20, 40);
  display.print("12H mode: ");
  display.println(settings.is12Hmode ? "yes" : " no");

  display.setCursor(12, 52);
  display.print(daysOfTheWeek[rtc.getDoW()]);
  display.print(", ");
  bool century;
  display.print(monthsOfTheYear[rtc.getMonth(century)]);
  display.print(' ');
  int day = rtc.getDate();
  print2DigitNumber(day, ' ');
  display.print(", ");
  display.println(2000 + rtc.getYear());

  bool fill = this->editing;
  switch (this->selectedField) {
    case 0:
      drawSelection(20, 19, 24, 18, fill);
      break;
    case 1:
      drawSelection(54, 19, 26, 18, fill);
      break;
    case 2:
      drawSelection(78, 38, 22, 12, fill);
      break;
    case 3:
      drawSelection(10, 50, 21, 12, fill);
      break;
    case 4:
      drawSelection(40, 50, 21, 12, fill);
      break;
    case 5:
      drawSelection(64, 50, 15, 12, fill);
      break;
    case 6:
      drawSelection(88, 50, 27, 12, fill);
      break;
  }
  display.drawRect(0, 0, 128, 64, WHITE);
}

void SetTimeMode::ok() {
  this->editing = !this->editing;
  this->refreshDisplay();
}

void SetTimeMode::cancel() { setMode(&menuMode); }

void SetTimeMode::plus() {
  if (this->editing) {
    bool is12h, isPM, century;
    int item;
    byte day, days;
    switch (this->selectedField) {
      case 0:
        item = rtc.getHour(is12h, isPM) + 1;
        rtc.setHour(item % 24);
        break;
      case 1:
        item = rtc.getMinute() + 1;
        rtc.setMinute(item % 60);
        rtc.setSecond(0);
        break;
      case 2:
        settings.is12Hmode = !settings.is12Hmode;
        saveSettings();
        break;
      case 3:
        item = rtc.getDoW() + 1;
        rtc.setDoW(item % 7);
        break;
      case 4:
        item = rtc.getMonth(century) + 1;
        rtc.setMonth((item - 1) % 12 + 1);
        break;
      case 5:
        day = rtc.getDate() + 1;
        item = rtc.getMonth(century);
        days = daysInMonth[item];
        if (item == 2 && rtc.getYear() % 4 == 0) days++;
        if (day > days) day = 1;
        rtc.setDate(day);
        break;
      case 6:
        item = rtc.getYear();
        if (item == 99) item = 0;
        rtc.setYear(item + 1);
        break;
    }
  } else {
    this->selectedField = (this->selectedField + 6) % 7;
  }
  this->refreshDisplay();
}

void SetTimeMode::minus() {
  if (this->editing) {
    bool is12h, isPM, century;
    int item;
    byte day;
    switch (this->selectedField) {
      case 0:
        item = rtc.getHour(is12h, isPM) - 1;
        rtc.setHour(item < 0 ? 23 : item);
        break;
      case 1:
        item = rtc.getMinute() - 1;
        rtc.setMinute(item < 0 ? 59 : item);
        break;
      case 2:
        settings.is12Hmode = !settings.is12Hmode;
        saveSettings();
        break;
      case 3:
        item = rtc.getDoW() - 1;
        rtc.setDoW(item < 0 ? 6 : item);
        break;
      case 4:
        item = rtc.getMonth(century) - 1;
        rtc.setMonth((item < 1 ? 12 : item));
        break;
      case 5:
        day = rtc.getDate() - 1;
        if (day < 1) {
          item = rtc.getMonth(century);
          day = daysInMonth[item];
          if (item == 2 && rtc.getYear() % 4 == 0) day++;
        }
        rtc.setDate(day);
        break;
      case 6:
        item = rtc.getYear();
        if (item == 0) item = 99;
        rtc.setYear(item - 1);
        break;
    }
  } else {
    this->selectedField = (this->selectedField + 1) % 7;
  }
  this->refreshDisplay();
}

SetTimeMode setTimeMode;
