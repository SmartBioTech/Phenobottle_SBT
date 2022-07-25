#!/bin/python3
import serial

def optical_density():
    ser.flush()
    ser.write(b'MeasureOpticalDensity')
    ser.flush()
    
    print("Measuring...")
    ser_bytes = ser.readline(20)
    light_intensity_a = str(ser_bytes[0:len(ser_bytes) - 2].decode("utf-8"))
    print("Optical density = ", light_intensity_a)


ser = serial.Serial('/dev/ttyACM0', 115200)

optical_density()

