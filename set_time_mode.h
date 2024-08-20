#pragma once

#include "mode.h"

class SetTimeMode : public Mode {
 private:
  int selectedField = 0;
  bool editing = false;

 public:
  void init() override;
  void displayMode() override;
  void ok() override;
  void cancel() override;
  void plus() override;
  void minus() override;
};

extern SetTimeMode setTimeMode;
