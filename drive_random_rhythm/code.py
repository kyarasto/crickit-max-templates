# --- Max sends 1-4, Crickit fires solenoid ---
# Uses boot.py 

import time
import board
import busio
import neopixel
import usb_cdc
from adafruit_seesaw.seesaw import Seesaw

serial = usb_cdc.data

# Connect to Crickit
i2c = busio.I2C(board.SCL, board.SDA)
ss = Seesaw(i2c, 0x49)

# Drive pins (seesaw pin numbers for Crickit drives 1-4)
DRIVE_PINS = (13, 12, 43, 42)
PULSE_TIME = 0.04  # 40 ms

# ---- Main Loop ----
while True:
    if serial.in_waiting > 0:
        raw = serial.read(1)
        if raw is None or len(raw) == 0:
            continue

        cmd = raw[0]

        if cmd < 1 or cmd > 4:
            continue

        pin = DRIVE_PINS[cmd - 1]

        try:
            ss.analog_write(pin, 65535)       # ON
            time.sleep(PULSE_TIME)
            ss.analog_write(pin, 0)           # OFF
        except OSError:
            pass
