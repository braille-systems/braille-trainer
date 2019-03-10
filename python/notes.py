import time
import serial
from serial_get_name import get_port_arduino


def startApp():
    pass


def startApp2():
    text = ''
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(3)  # если мало "поспать", не работает
    print('Type a letter:\n')
    btn_command = listen_button(ser)
    char = btn_to_char(btn_command)
    print(char)
    
    # while btn_command:
    #     char = btn_to_char(btn_command)
    #     # printLine(char)
    #     print(char)
    #     text = text + char
    
    ser.close()


def listen_button(ser):
    print('listen: ')
    ser.write(bytes('btn', 'UTF-8'))  # send arduino a request and wait a button command
    # arduino should write <button number><+/-> into serial
    # such as:
    line = ser.readline()
    while 1:
        _test_arduino(ser, '5+')
        print(line)
    print(line)
    print(6)
    return True


def _test_arduino(ser, text):
    ser.write(bytes(text, 'UTF-8'))
    print(4)


startApp()
