// --- Measure the loudness of the sound picked
// up by the Crickit mic and sent a byte to Max ---

#include <Adafruit_CircuitPlayground.h>

void setup() {
  Serial.begin(115200); // open serial
  delay(2000);                
  CircuitPlayground.begin();  
}

void loop() {
  // measure sound pressure level over a short window.
  float spl = CircuitPlayground.mic.soundPressureLevel(10);   // 10 ms of audio to average

  // map SPL range to 0–255.
  int level = map((int)spl, 50, 90, 0, 255);
  level = constrain(level, 0, 255);

  Serial.write((uint8_t)level);   // send one byte to Max

  delay(10);  
}
