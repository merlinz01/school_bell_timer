#pragma once

#define SSD1306_NO_SPLASH
#include <Adafruit_SSD1306.h>

#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

extern Adafruit_SSD1306 display;

void initDisplay();
void drawSelection(int16_t x, int16_t y, int16_t w, int16_t h, bool fill);
void drawCheck(int x, int y, bool checked);
void print2DigitNumber(uint8_t number, char fillChar);