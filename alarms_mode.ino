
#include "alarm_selection_mode.h"
#include "alarms_mode.h"
#include "display.h"
#include "settings.h"

void AlarmsMode::init() {
  this->selectedField = 0;
  this->editing = false;
}

char *letterDaysOfTheWeek = "SMTWTFS";

void AlarmsMode::displayMode() {
  drawCheck(5, 5, settings.alarms[this->selectedAlarm].enabled);

  display.setCursor(20, 2);
  display.setTextSize(2);
  display.print("Alarm ");
  display.print(this->selectedAlarm + 1);

  display.setTextSize(2);
  display.setCursor(15, 21);
  uint8_t hour = settings.alarms[this->selectedAlarm].hour;
  bool isPM = false;
  if (settings.is12Hmode) {
    isPM = hour >= 12;
    if (hour == 0) hour = 12;
    if (hour > 12) hour -= 12;
  }
  print2DigitNumber(hour, ' ');
  display.print(':');
  uint8_t minute = settings.alarms[this->selectedAlarm].minute;
  print2DigitNumber(minute, '0');
  if (settings.is12Hmode) {
    display.print(isPM ? " PM" : " AM");
  }

  for (int i = 0; i < 7; i++) {
    drawCheck(i * 15 + 13, 40,
              settings.alarms[this->selectedAlarm].weekdays & (1 << i));
    display.setCursor(i * 15 + 16, 52);
    display.setTextSize(1);
    display.print(letterDaysOfTheWeek[i]);
  }

  display.drawRect(0, 0, 128, 64, WHITE);

  bool fill = this->editing;
  switch (this->selectedField) {
    case 0:
      drawSelection(4, 4, 12, 12, true);
      break;
    case 1:
      drawSelection(14, 19, 25, 18, fill);
      break;
    case 2:
      drawSelection(49, 19, 26, 18, fill);
      break;
    default:
      drawSelection((this->selectedField - 3) * 15 + 12, 39, 12, 12, true);
      break;
  }
}

void AlarmsMode::ok() {
  if (this->selectedField == 1 || this->selectedField == 2) {
    this->editing = !this->editing;
  } else if (this->selectedField == 0) {
    settings.alarms[this->selectedAlarm].enabled =
        !settings.alarms[this->selectedAlarm].enabled;
    saveSettings();
  } else {
    settings.alarms[this->selectedAlarm].weekdays ^=
        (1 << (this->selectedField - 3));
    saveSettings();
  }
  this->refreshDisplay();
}

void AlarmsMode::cancel() { setMode(&alarmSelectionMode); }

void AlarmsMode::plus() {
  if (this->editing) {
    if (this->selectedField == 1) {
      settings.alarms[this->selectedAlarm].hour =
          (settings.alarms[this->selectedAlarm].hour + 1) % 24;
    } else if (this->selectedField == 2) {
      settings.alarms[this->selectedAlarm].minute =
          (settings.alarms[this->selectedAlarm].minute + 1) % 60;
    }
  } else
    this->selectedField = (this->selectedField + 9) % 10;
  this->refreshDisplay();
}

void AlarmsMode::minus() {
  if (this->editing) {
    if (this->selectedField == 1) {
      settings.alarms[this->selectedAlarm].hour =
          (settings.alarms[this->selectedAlarm].hour + 23) % 24;
    } else if (this->selectedField == 2) {
      settings.alarms[this->selectedAlarm].minute =
          (settings.alarms[this->selectedAlarm].minute + 59) % 60;
    }
  } else
    this->selectedField = (this->selectedField + 1) % 10;
  this->refreshDisplay();
}

void AlarmsMode::setAlarm(int alarm) { this->selectedAlarm = alarm; }

AlarmsMode alarmsMode;
