#!/bin/python3
import serial

def optical_density():
    ser.flush()
    ser.write(b'MeasureFluorescence')
    ser.flush()

    for _ in range(20000):
        fluorescence_bytes = ser.readline()
        decoded_fluorescence_bytes = str(fluorescence_bytes[0:len(fluorescence_bytes) - 2].decode("utf-8"))
        print(decoded_fluorescence_bytes)


ser = serial.Serial('/dev/ttyACM0', 115200)

optical_density()
