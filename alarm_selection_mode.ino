
#include "alarm_selection_mode.h"
#include "alarms.h"
#include "alarms_mode.h"
#include "display.h"
#include "menu_mode.h"
#include "settings.h"

void AlarmSelectionMode::displayMode() {
#define LINE_HEIGHT 22
  for (int i = this->topItem; i < NUM_ALARMS; i++) {
    int j = i - this->topItem;
    display.setTextSize(2);
    display.setCursor(2, j * LINE_HEIGHT + 3);
    if (i == this->selectedItem) {
      display.setTextColor(BLACK);
      display.fillRect(0, j * LINE_HEIGHT, 128, LINE_HEIGHT, WHITE);
    }
    display.print("Alarm ");
    print2DigitNumber(i + 1, ' ');
    display.setTextSize(1);
    display.setCursor(95, j * LINE_HEIGHT + 2);
    print2DigitNumber(settings.alarms[i].hour, ' ');
    display.print(':');
    print2DigitNumber(settings.alarms[i].minute, '0');
    drawCheck(107, j * LINE_HEIGHT + 10, settings.alarms[i].enabled);
    if (i == this->selectedItem) {
      display.setTextColor(WHITE);
    }
  }
#undef LINE_HEIGHT
}

void AlarmSelectionMode::ok() {
  alarmsMode.setAlarm(this->selectedItem);
  setMode(&alarmsMode);
}

void AlarmSelectionMode::cancel() { setMode(&menuMode); }

void AlarmSelectionMode::plus() {
  if (this->selectedItem > 0) this->selectedItem--;
  if (this->selectedItem < this->topItem) this->topItem--;
  this->refreshDisplay();
}

void AlarmSelectionMode::minus() {
  if (this->selectedItem + 1 < NUM_ALARMS) this->selectedItem++;
  if (this->selectedItem > this->topItem + 2) this->topItem++;
  this->refreshDisplay();
}

AlarmSelectionMode alarmSelectionMode;
