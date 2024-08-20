
#include "buzzer.h"
#include "display.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initDisplay() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    ring();
    while (1);  // halt
  }
  display.setRotation(2);
  display.setTextColor(WHITE);
}

void drawSelection(int16_t x, int16_t y, int16_t w, int16_t h, bool fill) {
  if (fill) {
    display.fillRect(x, y, w, h, INVERSE);
  } else {
    display.drawRect(x, y, w, h, WHITE);
  }
}

const uint8_t checkBitmap[8] = {
    0b00000000,  //
    0b00000001,  //
    0b00000011,  //
    0b00000110,  //
    0b11001100,  //
    0b01111000,  //
    0b00110000,  //
    0b00000000,  //
};

void drawCheck(int x, int y, bool checked) {
  display.drawRect(x, y, 10, 10, INVERSE);
  if (checked) {
    display.drawBitmap(x + 1, y + 1, checkBitmap, 8, 8, INVERSE);
  }
}

void print2DigitNumber(uint8_t number, char fillChar) {
  if (number < 10) display.print(fillChar);
  display.print(number);
}