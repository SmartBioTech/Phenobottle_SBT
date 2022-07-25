#!/bin/python3

import Motor_HAT
import time

mixing_motor        = Motor_HAT.Motor(0x41, 0)
bubling_motor       = Motor_HAT.Motor(0x40, 0, 50)
peristaltic_pump    = Motor_HAT.Motor(0x40, 1, 50)

run_time = 3

print("Mixing motor")
initial_mixing_speed = 5
motor_speed = 10

mixing_motor.Run('forward', initial_mixing_speed)
time.sleep(1)
mixing_motor.Run('forward', motor_speed)
time.sleep(run_time)
mixing_motor.Stop()

print("Bubling motor")
motor_speed = 30

bubling_motor.Run('forward', motor_speed)
time.sleep(run_time)
bubling_motor.Stop()

print("Peristaltic pump")
motor_speed = 100

peristaltic_pump.Run('forward', motor_speed)
time.sleep(run_time)
peristaltic_pump.Stop()
