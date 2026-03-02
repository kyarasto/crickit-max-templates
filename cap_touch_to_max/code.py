# --- Crickit touch pads to Max/MSP ---
# Uses boot.py 

import time
import board
import busio
import neopixel
import usb_cdc
from adafruit_seesaw.seesaw import Seesaw
from adafruit_seesaw.crickit import Crickit_Pinmap

serial = usb_cdc.data

i2c = busio.I2C(board.SCL, board.SDA)
ss = Seesaw(i2c, 0x49)

TOUCH_PINS = Crickit_Pinmap.touch_pins
NUM_PADS = 4
TOUCH_THRESHOLD = 150

baseline = [0] * NUM_PADS
for p in range(NUM_PADS):
    total = 0
    for _ in range(20):
        total += ss.touch_read(TOUCH_PINS[p])
        time.sleep(0.005)
    baseline[p] = total // 20

was_touched = [False] * NUM_PADS

while True:
    for i in range(NUM_PADS):
        value = ss.touch_read(TOUCH_PINS[i])
        touched = value > (baseline[i] + TOUCH_THRESHOLD)

        if touched and not was_touched[i]:
            was_touched[i] = True
            serial.write(bytes([i + 1]))

        elif not touched and was_touched[i]:
            was_touched[i] = False

    time.sleep(0.01)
