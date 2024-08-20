#pragma once

class Mode {
 public:
  void refreshDisplay();
  virtual void init();
  virtual void displayMode();
  virtual void loop();
  virtual void ok();
  virtual void cancel();
  virtual void plus();
  virtual void minus();
};

extern Mode *current_mode;

void setMode(Mode *mode);
