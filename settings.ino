#include "eeprom.h"
#include "settings.h"

Settings settings;

void loadSettings() {
  mem.get(0, settings);
  if (settings.validFlag != VALID_FLAG) {
    memcpy(settings.validFlag, VALID_FLAG, sizeof(settings.validFlag));
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

void saveSettings() { mem.putChanged(0, settings); }