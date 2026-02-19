# Crickit + Max  Templates

This repo has example projects for using an **Adafruit Crickit** with **Max MSP**.

Each folder contains:
- An Arduino sketch (.ino) for the Crickit
- A Max patch (.maxpat) that talks to the board over USB serial

## What You Need

#### Hardware

- Adafruit Crickit for Circuit Playground Express  
- 5V 2A power supply (barrel jack) — required for motors, servos, and solenoids  
- USB Micro-B cable (to computer)

#### For Specific Actuators

- **Servo**: Plug into Servo 1 terminal.  
- **DC Motor**: 5V DC motor. Screw wires into Motor 1 terminal block.  
- **Solenoid**: 5V solenoid. One wire to 5V terminal, other to Drive 1 (or 2/3/4).  

#### Software

- Arduino IDE 
- Max/MSP 

## Arduino IDE Setup 

#### Add the Adafruit Board Package

1. Go to **Arduino IDE → Settings**  
2. In **Additional Board Manager URLs**, paste:  
https://adafruit.github.io/arduino-board-index/package_adafruit_index.json

4. Go to **Tools → Board → Board Manager**, search **Adafruit SAMD**, and install it.

#### Select the Board

- Tools → Board → Adafruit SAMD → Adafruit Circuit Playground Express

#### Install Libraries

Go to Tools → Manage Libraries and install:

- **Adafruit seesaw Library**  
- **Adafruit Circuit Playground**  

#### Select the Port

1. Plug in your CPX via USB  
2. Go to **Tools → Port** and select the correct port  
- macOS: `/dev/cu.usbmodem...`

## Templates

|   | Template | What It Does |
|---|---------|--------------|
| 1 | Servo | Random notes mapped to servo angles |
| 2 | LEDs | Random notes mapped to RGB colors on NeoPixels |
| 3 | DC Motor | Random speed/direction |
| 4 | Solenoid / Drive | Random percussive hits |
| 5 | Speaker | Random MIDI notes played as tones |
| 6 | Mic | Loudness controls volume or pitch in Max |
| 7 | Cap Touch | 4 touch pads trigger 4 notes |

## Template Folders

### 1. servo_random_melody
- Max generates random notes and random timing.
- The Arduino sketch receives values (0–180) and moves a servo between angles.

### 2. leds_from_max
- Max sends values 0–127 to control the CPX NeoPixels.
- Arduino maps that into colors on all 10 LEDs.

### 3. motor_random_max
- Max sends byte 0-255 to arduino.
- Arduino maps this to a throttle for the motor.

### 4. drive_random_rhythm
- Max sends byte 1-4 to arduino.
- Arduino fires the corresponding drive pin.

### 5. speaker_random_melody
- Max sends a MIDI note (36-96).
- Arduino maps to a frequency and plays the tone.

### 6. mic_to_max
- CPX microphone measures sound pressure level.
- Arduino sends a byte 0–255 representing loudness.
- Max uses this to control volume or pitch.

### 7. cap_touch_to_max
- Arduino sends 1, 2, 3, or 4 when a pad is touched.
- Max routes those into different notes.

  
## How to use 

1. **Arduino side**
   - Open the .ino file in the Arduino IDE.
   - Select the **Adafruit Circuit Playground Express** in port.
   - Upload the code.
   - Close the Arduino Serial Monitor if it’s open.

2. **Max side**
   - Open the matching .maxpat file.
   - Click the 'print' message and look in the Max console for the correct 'port x' (usbmodem…).
   - Click the corresponding 'port d' message (or change it to whichever letter matches).
   - Turn on audio / metro / toggle.
   - Make sure both the Arduino sketch and Max patch use the same baud rate (115200).

3. **Play**
   - Interact with the hardware (mic, capacitive pads)!
