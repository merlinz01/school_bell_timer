
#include <Wire.h>

#include "alarms.h"
#include "buttons.h"
#include "buzzer.h"
#include "display.h"
#include "eeprom.h"
#include "mode.h"
#include "rtc.h"
#include "settings.h"
#include "time_display_mode.h"

void setup() {
  Wire.begin();
  initBuzzer();
  initDisplay();
  initEEPROM();
  loadSettings();
  initRtc();
  initButtons();
  setMode(&timeDisplayMode);
}

void loop() {
  checkAlarms();
  checkButtons();
  current_mode->loop();
  delay(10);
}
