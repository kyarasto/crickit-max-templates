# --- Max sends 0-255, Crickit controls DC motor ---
# Uses boot.py

import gc
gc.collect()
import usb_cdc

serial = usb_cdc.data

gc.collect()
import board
import busio
from adafruit_seesaw.seesaw import Seesaw
gc.collect()
from adafruit_seesaw.pwmout import PWMOut
gc.collect()

i2c = busio.I2C(board.SCL, board.SDA)
ss = Seesaw(i2c, 0x49)
gc.collect()

# CRICKIT_MOTOR_A1 = 22, CRICKIT_MOTOR_A2 = 23
motor_a1 = PWMOut(ss, 22)
gc.collect()
motor_a2 = PWMOut(ss, 23)
gc.collect()

# Start stopped
motor_a1.duty_cycle = 0
motor_a2.duty_cycle = 0

# Main Loop
while True:
    if serial.in_waiting > 0:
        raw = serial.read(1)
        if raw and len(raw) > 0:
            byte_val = raw[0]

            # 0=full reverse, 127=stop, 255=full forward
            if 122 <= byte_val <= 132:
                # stop at 127
                motor_a1.duty_cycle = 0
                motor_a2.duty_cycle = 0
            elif byte_val > 132:
                # forward: a1 = speed, a2 = 0
                speed = ((byte_val - 127) * 65535) // 128
                motor_a1.duty_cycle = speed
                motor_a2.duty_cycle = 0
            else:
                # reverse: a1 = 0, a2 = speed
                speed = ((127 - byte_val) * 65535) // 128
                motor_a1.duty_cycle = 0
                motor_a2.duty_cycle = speed
