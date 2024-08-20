
#include "alarm_selection_mode.h"
#include "display.h"
#include "menu_mode.h"
#include "mode.h"
#include "set_time_mode.h"
#include "time_display_mode.h"

MenuMode::MenuMode(MenuItem *items, int nItems)
    : items(items), nItems(nItems), selectedItem(0) {}

void MenuMode::displayMode() {
#define LINE_HEIGHT 22
  display.setTextSize(2);
  for (int i = 0; i < this->nItems; i++) {
    display.setCursor(2, i * LINE_HEIGHT + 3);
    if (i == this->selectedItem) {
      display.setTextColor(BLACK);
      display.fillRect(0, i * LINE_HEIGHT, 128, LINE_HEIGHT - 1, WHITE);
    }
    display.println(this->items[i].label);
    if (i == this->selectedItem) {
      display.setTextColor(WHITE);
    }
  }
#undef LINE_HEIGHT
}

void MenuMode::ok() { setMode(this->items[this->selectedItem].mode); }

void MenuMode::cancel() { setMode(&timeDisplayMode); }

void MenuMode::plus() {
  if (this->selectedItem > 0) this->selectedItem--;
  this->refreshDisplay();
}

void MenuMode::minus() {
  if (this->selectedItem + 1 < this->nItems) this->selectedItem++;
  this->refreshDisplay();
}

MenuItem mItems[] = {
    {"Show time", &timeDisplayMode},
    {"Set time", &setTimeMode},
    {"Alarms", &alarmSelectionMode},
};

MenuMode menuMode = MenuMode(mItems, 3);
