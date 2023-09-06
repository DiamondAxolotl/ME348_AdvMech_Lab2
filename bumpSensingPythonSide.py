#!/usr/bin/env python3
import serial
import time
import numpy as np
#import matplotlib as plt

from sendStringScript import sendString
leftMotor=int(100)
rightMotor=int(100)      

if __name__ == '__main__':
    ser=serial.Serial('/dev/ttyACM0',115200)
    #every time the serial port is opened, the arduino program will restart, very convient!
    ser.reset_input_buffer()
    ready = 0

    while True: 

        
        if ready == 0:
            line = ser.readline().decode('utf-8')
            print(line) 
            ready = 1 #we wait until arduino has sent its first full line (<arduino is ready>) line before sending anything to arduino, 
                    #this gives arduino time to set up, np matter how long that time is
            

        if ready ==1:
            sendString('/dev/ttyACM0',115200,'<'+str(leftMotor)+','+str(rightMotor)+'>',0.0005)
            # ser.write(b'<'+bytes(str(leftMotor),'utf-8')+b','+bytes(str(rightMotor),'utf-8')+b'>')

            #theses are 2 seprate methods to send a string from the rpi to the arduino, you can use the serial moniter on the arduino
            #side to examine what the string looks like when it arrives to the arduino. What do you notice?
            #is one of these 2 methods better than the other? which one? use the internet to try to figure out why one of these 
            #methods works better than the other (I'm not totally sure myself even thought I wrote the sendString() function to solve 
            #this problem)


            if ser.in_waiting > 0:
                line = ser.readline().decode('utf-8')
                #ive just called 2 methods from the ser object, what do they do? read the documentation and find out!
                line=line.split(',')
                #this one i wont ask you about this one is pretty self explanitory
                try:
                    
                    x=int(line[0])
                    y=int(line[1])
                    z=int(line[2])

                    a=int(line[3])
                    b=int(line[4])
                    c=int(line[5])

                    print([x,y,z,a,b,c])
                
                except:
                    print("packetLost") 
                #why do I have this exepction? 

                #your state machine can go here
