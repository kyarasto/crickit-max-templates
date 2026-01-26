// --- Use the 4 capacitive touch pads on the Crickit to play notes on Max ---

#include <Adafruit_Crickit.h>

Adafruit_Crickit crickit;

const int NUM_PADS = 4;          // four pads on Crickit
uint16_t baseline[NUM_PADS];
bool    wasTouched[NUM_PADS];
bool    crickit_ok = false;

// how much above baseline counts as touched
const uint16_t TOUCH_THRESHOLD = 150;

void setup() {
  Serial.begin(115200); //open serial
  delay(2000);

  Serial.println("Starting Crickit...");
  if (!crickit.begin()) {
    Serial.println("Crickit not found");
    return;
  }
  crickit_ok = true;
  Serial.println("Crickit started");

  // check baseline for each pad
  for (int p = 0; p < NUM_PADS; p++) {
    uint32_t sum = 0;
    const int samples = 20;
    for (int i = 0; i < samples; i++) { // take samples to get
      sum += crickit.touchRead(p);      // baseline when nothing touching
      delay(5);
    }
    baseline[p] = sum / samples;
    wasTouched[p] = false;
  }
}

void loop() {
  if (!crickit_ok) {
    delay(1000);
    return;
  }

  for (int p = 0; p < NUM_PADS; p++) {   // check each pad on every loop
    uint16_t value = crickit.touchRead(p); 
    bool touched = (value > baseline[p] + TOUCH_THRESHOLD); //check if touched with baseline

    if (touched && !wasTouched[p]) {
      wasTouched[p] = true;

      uint8_t id = p + 1;        // make pad index 0-3 to numbers 1-4
      Serial.write(id);          // send one byte to Max
    } else if (!touched && wasTouched[p]) {
      wasTouched[p] = false; // released
    }
  }

  delay(10);
}
