
#include "buzzer.h"

void initBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
  analogWriteResolution(10);
}

void ring() {
  for (int x = 0; x < 15; x++) {
    for (int x = 0; x < 200; x++) {
      delayMicroseconds(500);
      digitalWrite(BUZZER_PIN, HIGH);
      delayMicroseconds(300);
      digitalWrite(BUZZER_PIN, LOW);
    }
    delay(15);
  }
}