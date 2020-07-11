import pyaudio
import numpy as np
import time

p = pyaudio.PyAudio()
delay = 0.1     # time between each bit is sent
volume = 1.0     # range [0.0, 1.0]
fs = 44100       # sampling rate, Hz, must be integer
duration = 0.1   # in seconds, may be float
f = 700.0        # sine frequency, Hz, may be float

def WriteData(instruction, device, value):
    DList = [int(instruction), int(device), int(value)]
    data = bytearray(DList)
    Transmit(data)
    #print(data)
    #for byte in data:
        #print (bin(byte)[3])
        #for b in bin(byte)[2:]:
        #print(bin(byte)[2:])
           #print(b)

def getData():
    instruction, device, value = input("Enter Instruction Set: ").split()
    WriteData(instruction, device, value)

def Transmit(data):

    
    # generate samples, note conversion to float32 array
    samples = (np.sin(2*np.pi*np.arange(fs*duration)*f/fs)).astype(np.float32)

    # for paFloat32 sample values must be in range [-1.0, 1.0]
    stream = p.open(format=pyaudio.paFloat32,
                    channels=1,
                    rate=fs,
                    output=True)

    # play. May repeat with different volume values (if done interactively)
    
    stream.write(volume*samples) #wakeup bit
    time.sleep(1)
    stream.write(volume*samples) #wakeup bit


    for byte in data:
        #print(format(byte, '#010b')[2:])
        for b in format(byte, '#010b')[2:]:
            #print(b)
            if b == '1':   
                stream.write(volume*samples)
            time.sleep(delay)
                

    stream.stop_stream()

    stream.close()

    p.terminate()

getData()
