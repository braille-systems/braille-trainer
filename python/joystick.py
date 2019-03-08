import serial
import time
import serial_get_name as sg


def listen_joystick(ser):
    """
    "ser" is an open Serial connection with Braille trainer
    (with Arduino board having '../arduino/printText/printText.ino' sketch loaded).

    Returns the joystick answer as a letter (l, r, d or u).
    """
    print('listen: ')
    ser.flushInput()
    ser.write(bytes('?', 'UTF-8'))
    line = ser.readline()
    letter = str(line)[2]
    print(line)
    return letter if letter in ['l', 'r', 'd', 'u'] else True


if __name__ == "__main__":
    ser = serial.Serial(sg.get_port_arduino(), '9600')
    time.sleep(5)
    print(sg.get_port_arduino())
    print(listen_joystick(ser))
    print(listen_joystick(ser))
    ser.close()
