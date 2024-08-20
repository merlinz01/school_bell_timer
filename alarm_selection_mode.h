#pragma once

#include "mode.h"

class AlarmSelectionMode : public Mode {
 protected:
  int selectedItem;
  int topItem;

 public:
  void displayMode() override;
  void ok() override;
  void cancel() override;
  void plus() override;
  void minus() override;
};

extern AlarmSelectionMode alarmSelectionMode;
