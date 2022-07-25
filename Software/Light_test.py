#!/bin/python3
import serial
import time

def light_on(red_intensity, green_intensity, blue_intensity):
    str_red = bytes(str(red_intensity), "utf-8")
    str_green = bytes(str(green_intensity), "utf-8")
    str_blue = bytes(str(blue_intensity), "utf-8")
    ser.write(b'RGB_light_ON;%s;%s;%s;%s;%s;%s' %("36".encode("utf-8"), 
    	str_red, "37".encode("utf-8"), str_green, "38".encode("utf-8"), str_blue))
    ser.flush()

def light_off():
    ser.write(b'RGB_light_OFF')

sleep_time = 1

red = 255
green = 255
blue = 255

ser = serial.Serial('/dev/ttyACM0', 115200)

light_on(red, 0, 0)
time.sleep(sleep_time)
light_on(0, green, 0)
time.sleep(sleep_time)
light_on(0, 0, blue)
time.sleep(sleep_time)
light_on(0,0,0)

