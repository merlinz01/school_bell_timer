
#include <ArduinoLowPower.h>
#include <Wire.h>
#include <wdt_samd21.h>

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
  savePower();
  Wire.begin();
  initBuzzer();
  initDisplay();
  initEEPROM();
  loadSettings();
  initRtc();
  initButtons();
  setMode(&timeDisplayMode);
  initWatchdog();
}

void loop() {
  checkAlarms();
  checkButtons();
  current_mode->loop();
  delay(10);
  wdt_reset();
}

void savePower() {
  // Disable unused peripherals
  LowPower.detachAdcInterrupt();
}

void initWatchdog() { wdt_init(WDT_CONFIG_PER_8K); }
