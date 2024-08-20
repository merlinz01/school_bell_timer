#pragma once

#include "mode.h"

class AlarmsMode : public Mode {
 private:
  int selectedAlarm = 0;
  int selectedField = 0;
  bool editing = false;

 public:
  void init() override;
  void displayMode() override;
  void ok() override;
  void cancel() override;
  void plus() override;
  void minus() override;

  void setAlarm(int alarm);
};

extern AlarmsMode alarmsMode;