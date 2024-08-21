#pragma once

#include "buzzer.h"
#include "menu_mode.h"

class TimeDisplayMode : public Mode {
 public:
  void init() override;
  void displayMode() override;
  void ok() override;
  void cancel() override;
  void plus() override;
  void minus() override;
  void loop() override;

 private:
  int lastSecond = -1;
};

extern TimeDisplayMode timeDisplayMode;
