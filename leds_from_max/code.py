# --- Max sends 0-127 to change NeoPixel color ---
# uses boot.py

import board
import neopixel
import usb_cdc

pixels = neopixel.NeoPixel(board.NEOPIXEL, 10, brightness=0.3, auto_write=False)
pixels.fill((0, 0, 0))
pixels.show()

serial = usb_cdc.data
if serial is None:
    import time
    while True:
        pixels.fill((255, 0, 0))
        pixels.show()
        time.sleep(0.3)
        pixels.fill((0, 0, 0))
        pixels.show()
        time.sleep(0.3)

def map_range(value, in_min, in_max, out_min, out_max):
    return int((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

while True:
    if serial.in_waiting > 0:
        raw = serial.read(1)
        if raw is None or len(raw) == 0:
            continue

        v = raw[0]
        level = max(0, min(255, map_range(v, 0, 127, 0, 255)))

        red   = level
        blue  = 255 - level
        green = level // 4

        pixels.fill((red, green, blue))
        pixels.show()
