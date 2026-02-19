// --- Max sends a byte to control a DC motor on the Crickit ----

#include "Adafruit_Crickit.h"   
#include "seesaw_motor.h"       // motor helper

Adafruit_Crickit crickit;
seesaw_Motor motor(&crickit);   // motor object talks through Crickit

bool crickit_ok = false;

void setup() {
  Serial.begin(115200);        
  delay(2000);                

  if (!crickit.begin()) {
    Serial.println("Crickit not found");
    return;
  }

  crickit_ok = true;
  Serial.println("Crickit okay – motor ready!");

  // attach motor to Motor 1 terminal 
  motor.attach(CRICKIT_MOTOR_A1, CRICKIT_MOTOR_A2);

  motor.throttle(0);
}

void loop() {
  if (!crickit_ok) {            
    delay(1000);
    return;
  }

  if (Serial.available() > 0) {
    int raw = Serial.read();    // read one byte from Max (0–255)

    // convert 0–255 into a throttle from –1.0 to +1.0
    //   0   → –1.0  (reverse)
    //   127 →  0.0  (stop)
    //   255 → +1.0  (forward)
    float throttle = ((float)raw - 127.0) / 128.0;

    // motor stops
    if (throttle > -0.05 && throttle < 0.05) {
      throttle = 0;
    }

    throttle = constrain(throttle, -1.0, 1.0);

    motor.throttle(throttle);   // set motor speed & direction

    Serial.print("Byte: ");
    Serial.print(raw);
    Serial.print("Throttle: ");
    Serial.println(throttle);
  }
}
