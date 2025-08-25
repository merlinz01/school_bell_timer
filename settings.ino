#include "eeprom.h"
#include "settings.h"

Settings settings;

void loadSettings() {
  mem.get(SETTINGS_ADDRESS, settings);
  if (settings.validFlag != VALID_FLAG) {
    settings.validFlag = VALID_FLAG;
    settings.is12Hmode = true;
    for (int i = 0; i < NUM_ALARMS; i++) {
      settings.alarms[i].hour = 0;
      settings.alarms[i].minute = 0;
      settings.alarms[i].enabled = false;
      settings.alarms[i].weekdays = 0;
    }
    saveSettings();
  }
}

void saveSettings() { mem.putChanged(SETTINGS_ADDRESS, settings); }