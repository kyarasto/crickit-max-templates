// ---- Max sends a byte (0–180) and the Crickit moves the servo ----

#include "Adafruit_Crickit.h"
#include "seesaw_servo.h"

Adafruit_Crickit crickit;
seesaw_Servo myservo(&crickit);

bool crickit_ok = false;

// remember where the servo is now
int currentAngle = 90;

void setup() {
  Serial.begin(115200); // start serial
  delay(2000);  

  if (!crickit.begin()) {
    Serial.println("Crickit not found");
    return;
  }

  crickit_ok = true;
  Serial.println("Crickit okay!");

  myservo.attach(CRICKIT_SERVO1);
  myservo.write(currentAngle);   // start centered
}

void loop() {
  if (!crickit_ok) { // if Crickit failed 
    delay(1000);
    return;
  }

  if (Serial.available() > 0) {
    int targetAngle = Serial.read();   // read raw byte from serial (0–255)

    Serial.print("Byte: ");
    Serial.println(targetAngle);

    // only allow 0–180
    if (targetAngle < 0 || targetAngle > 180) {
      Serial.println("Out of range, ignoring.");
      return;
    }

    // smooth glide from currentAngle targetAngle
    int step;
    if (targetAngle > currentAngle) {
      step = 1;    // move up
    } else {
      step = -1;   // move down or stay
    }
    int stepDelay = 10;  // ms between steps 

    while (currentAngle != targetAngle) { // move one step until angle is the target
      currentAngle += step;
      myservo.write(currentAngle);
      delay(stepDelay);
    }

    Serial.print("Moved servo to ");
    Serial.print(currentAngle);
    Serial.println(" degrees");
  }
}
