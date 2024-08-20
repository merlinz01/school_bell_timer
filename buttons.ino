
#include "buttons.h"
#include "mode.h"

void initButtons() {
  pinMode(PLUS, INPUT_PULLUP);
  pinMode(MINUS, INPUT_PULLUP);
  pinMode(OK, INPUT_PULLUP);
  pinMode(CANCEL, INPUT_PULLUP);
}

struct {
  int b_PLUS;
  unsigned long b_PLUS_time;
  int b_MINUS;
  unsigned long b_MINUS_time;
  int b_OK;
  unsigned long b_OK_time;
  int b_CANCEL;
  unsigned long b_CANCEL_time;
} BUTTONS;

void checkButtons() {
  int bval;
#define CHECKBTN(b, handler, repeat)                                           \
  {                                                                            \
    if ((bval = digitalRead(b)) != BUTTONS.b_##b) {                            \
      if (!(BUTTONS.b_##b = bval)) {                                           \
        if (repeat) BUTTONS.b_##b##_time = millis() + BUTTON_REPEAT_DELAY * 3; \
        delay(DEBOUNCE_DELAY);                                                 \
        current_mode->handler();                                               \
      }                                                                        \
    } else if (repeat && !bval &&                                              \
               millis() > BUTTONS.b_##b##_time + BUTTON_REPEAT_DELAY) {        \
      current_mode->handler();                                                 \
      BUTTONS.b_##b##_time = millis();                                         \
    }                                                                          \
  }
  CHECKBTN(PLUS, plus, 1);
  CHECKBTN(MINUS, minus, 1);
  CHECKBTN(OK, ok, 0);
  CHECKBTN(CANCEL, cancel, 0);
#undef CHECKBTN
}
