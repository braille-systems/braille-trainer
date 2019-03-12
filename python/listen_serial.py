import serial
import time
import serial_get_name as sg


def listen_serial(ser):
    # Returns l, r, d, u or char in format 110000 (means 'б')
    print('listen joystick or keyboard:')
    
    ser.flushInput()
    ser.write(bytes('?', 'UTF-8'))
    line = ser.readline()
    s = str(line)
    if s[2] in 'ldru':
        return s[2]
    if s[2] in '01':
        return s[2:8]
    return True
    
    #return input()


if __name__ == "__main__":
    ser = serial.Serial(sg.get_port_arduino(), '9600')
    time.sleep(5)
    print(sg.get_port_arduino())
    print(listen_serial(ser))
    ser.close()
