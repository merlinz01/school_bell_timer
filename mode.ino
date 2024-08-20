
#include "display.h"
#include "mode.h"

Mode *current_mode = NULL;

void Mode::refreshDisplay() {
  display.clearDisplay();
  this->displayMode();
  display.display();
}
void Mode::init() {}
void Mode::displayMode() { display.println("Hello\nWorld!"); }
void Mode::loop() {}
void Mode::ok() {}
void Mode::cancel() {}
void Mode::plus() {}
void Mode::minus() {}

void setMode(Mode *mode) {
  current_mode = mode;
  mode->init();
  mode->refreshDisplay();
}
