// --- Max sends 0-127 RGB values which is mapped to a color for the NeoPixels on the Crickit ---

#include <Adafruit_CircuitPlayground.h>

int lastValue = 0; // store most recent color

void setup() {
  Serial.begin(115200); // open serial connection
  delay(2000); 

  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(80);

  Serial.println("Send one byte 0–127 from Max.");
}

void loop() {

  if (Serial.available() > 0) { // check if max sent a byte
    int v = Serial.read();  
    if (v < 0) return;

    lastValue = v;
    Serial.print("Got LED value: ");
    Serial.println(v);

    // map 0–127 to 0–255 for brightness & color
    uint8_t level = constrain(map(v, 0, 127, 0, 255), 0, 255);

    // color mapping:
    uint8_t red   = level;
    uint8_t blue  = 255 - level;
    uint8_t green = level / 4; 

    // set 10 pixels to that color
    for (int i = 0; i < 10; i++) {
      CircuitPlayground.setPixelColor(i, red, green, blue);
    }
  }
}
