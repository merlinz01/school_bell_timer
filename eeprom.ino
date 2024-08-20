#include "buzzer.h"
#include "display.h"
#include "eeprom.h"

void initEEPROM() {
  if (mem.begin() == false) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("No memory!");
    display.display();
    ring();
    while (1);
  }
  mem.setMemoryType(2);
}
