# Crickit + Max  Templates

This repo has example projects for using an **Adafruit Crickit** with **Max MSP**.

Each folder contains:
- An Arduino sketch (.ino) for the Crickit
- A Max patch (.maxpat) that talks to the board over USB serial

## Examples

### servo_random_melody
- Max generates random notes and random timing.
- The Arduino sketch receives values (0–180) and moves a servo between angles.

### leds_from_max
- Max sends values 0–127 to control the CPX NeoPixels.
- Arduino maps that into colors on all 10 LEDs.

### mic_to_max
- CPX microphone measures sound pressure level.
- Arduino sends a byte 0–255 representing loudness.
- Max uses this to control volume or pitch.

### cap_touch_to_max
- Arduino sends 1, 2, 3, or 4 when a pad is touched.
- Max routes those into different notes.

## How to use 

1. **Arduino side**
   - Open the .ino file in the Arduino IDE.
   - Go to Tools → Board → Boards Manager
   - Type: "Adafruit SAMD" and install “Adafruit SAMD Boards” 
   - Select the **Adafruit Circuit Playground Express** in port.
   - Upload the code.
   - Close the Arduino Serial Monitor if it’s open.

2. **Max side**
   - Open the matching .maxpat file.
   - Click the 'print' message and look in the Max console for the correct 'port x' (usbmodem…).
   - Click the corresponding 'port d' message (or change it to whichever letter matches).
   - Turn on audio / metro / toggle.

3. **Play**
   - Interact with the hardware (mic, capacitive pads)!
