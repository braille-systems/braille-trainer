from audio import playSoundByFilename
from serial_hex import printLine
import serial
import time
from serial_get_name import *
from datetime import datetime



def curr_time():
    """
    Returns the current time string.
    """
    dt = datetime.now()
    hour = dt.hour
    minute = dt.minute
    hm = str(hour) + ' ' + str(minute)
    # print(hm)
    # ser.write(bytes(hm, 'UTF-8'))
    return hm


def startApp(ser):
    """
    This is the Clock app for braille trainer.
    Designed to display current time.

    "ser" is an open Serial connection with Braille trainer
    (with Arduino board having '../arduino/printText/printText.ino' sketch loaded).
    """
    playSoundByFilename('audio/std_msg/cur_time.wav')
    printLine(curr_time(), ser)
    print(curr_time())


if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(3)  # если мало "поспать", не работает
    res = startApp(ser)
    ser.close()
