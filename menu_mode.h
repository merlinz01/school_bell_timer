#pragma once

#include "mode.h"

typedef struct {
  String label;
  Mode *mode;
} MenuItem;

class MenuMode : public Mode {
 protected:
  MenuItem *items;
  int nItems;
  int selectedItem;

 public:
  MenuMode(MenuItem *items, int nItems);
  void displayMode() override;
  void ok() override;
  void cancel() override;
  void plus() override;
  void minus() override;
};

extern MenuMode menuMode;
