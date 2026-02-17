// ---- Max sends a byte (1–4) to fire one of four solenoids on the Crickit ----

#include "Adafruit_Crickit.h"

Adafruit_Crickit crickit;

bool crickit_ok = false;

// array of the four drive pins
const int num_drives = 4;
int drives[] = { CRICKIT_DRIVE1, CRICKIT_DRIVE2, CRICKIT_DRIVE3, CRICKIT_DRIVE4 };

// how long each solenoid pulse lasts (in ms)
const int PULSE_MS = 40;

void setup() {
  Serial.begin(115200);        // open serial
  delay(2000);

  if (!crickit.begin()) {
    Serial.println("Crickit not found");
    return;
  }

  crickit_ok = true;
  Serial.println("Crickit okay – drives ready!");

  for (int i = 0; i < num_drives; i++) {  // set PWM frequency for each drive pin 
    crickit.setPWMFreq(drives[i], 1000);
    crickit.analogWrite(drives[i], 0);    // start with all drives off
  }
}

void loop() {
  if (!crickit_ok) {
    delay(1000);
    return;
  }

  if (Serial.available() > 0) {
    int cmd = Serial.read();       // read one byte from Max

    if (cmd < 1 || cmd > 4){      // only respond to 1, 2, 3, or 4
      return;
    }
    int pin = drives[cmd - 1];    // map 1–4 to array index 0–3

    // fire solenoid with a pulse
    crickit.analogWrite(pin, CRICKIT_DUTY_CYCLE_MAX);   // ON 
    delay(PULSE_MS);
    crickit.analogWrite(pin, 0);                        // OFF

    Serial.print("Fired drive ");
    Serial.println(cmd);
  }
}
