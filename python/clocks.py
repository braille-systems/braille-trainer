from curr_time import curr_time
from audio import playSoundByFilename
from serial_hex import printLine
import serial
import time
from serial_get_name import *
def startApp(ser):
    playSoundByFilename('audio/std_msg/cur_time.wav')
    printLine(curr_time(),ser)
    print(curr_time())
    
if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(3)  # если мало "поспать", не работает
    res = startApp(ser)
    ser.close()
