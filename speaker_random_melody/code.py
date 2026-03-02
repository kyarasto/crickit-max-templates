# --- Max sends MIDI note, speaker plays tone ---
# Uses boot.py

import math
import board
import digitalio
import simpleio
import usb_cdc

SPEAKER_PIN = board.SPEAKER
NOTE_DURATION = 0.15

try:
    speaker_enable = digitalio.DigitalInOut(board.SPEAKER_ENABLE)
    speaker_enable.direction = digitalio.Direction.OUTPUT
    speaker_enable.value = True
except Exception:
    pass

serial = usb_cdc.data
if serial is None:
    import time
    import neopixel
    pixels = neopixel.NeoPixel(board.NEOPIXEL, 10, brightness=0.3)
    while True:
        pixels.fill((255, 0, 0))
        time.sleep(0.3)
        pixels.fill((0, 0, 0))
        time.sleep(0.3)

def midi_to_freq(note):
    return 440.0 * math.pow(2.0, (note - 69.0) / 12.0)

while True:
    if serial.in_waiting > 0:
        raw = serial.read(1)
        if raw is None or len(raw) == 0:
            continue

        note = raw[0]
        if note == 0:
            continue

        freq = midi_to_freq(note)
        simpleio.tone(SPEAKER_PIN, freq, duration=NOTE_DURATION)
