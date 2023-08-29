#!/usr/bin/env python3
import serial
import time
import numpy as np
import matplotlib as plt

from sendStringScript import sendString
leftMotor=int(100)
rightMotor=int(100)


if __name__ == '__main__':
    ser=serial.Serial('/dev/ttyACM0',115200)
    #every time the serial port is opened, the arduino program will restart
    ser.reset_input_buffer()
    ready = 0

    while True:  
        if ready == 0:
            line = ser.readline().decode('utf-8')
            print(line)
            ready = 1 #we wait until arduino has sent its first full line (<arduino is ready>) line before sending anything to arduino, this gives arduino time to set up, np matter how long that time is
            

        if ready ==1:
            sendString('/dev/ttyACM0',115200,'<'+str(leftMotor)+','+str(rightMotor)+'>',0.0005)


            
            if ser.in_waiting > 0:  
                line = ser.readline().decode('utf-8')
                # print(line)
                line=line.split(',')
                try:
                    
                    x=int(line[0])
                    y=int(line[1])
                    z=int(line[2])
                    print([x,y,z])
                except:
                    print("packetLost")  
