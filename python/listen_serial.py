import serial
import time
import serial_get_name as sg
import help as hp


def listen_serial(ser, menuID=-1, requiresReturn =False):
    # Returns l, r, d, u or char in format 110000 (means 'б')
    print('listen joystick or keyboard:')
    #ser.flushInput()
    ser.write(bytes('?', 'UTF-8'))
    line = ser.readline()
    s = str(line)
    print(s[2])
    while not (s[2] in 'ldru01h+'):
        print('not in ldru01h+')
        line = ser.readline()
        s = str(line)
    if s[2] in 'ldru':
        return s[2]
    if s[2] in '01':
        return s[2:8]
    if (s[2] in 'h') & (menuID != -1):
        hp.instantHelp(menuID)
        #TODO: return something
        return s[2]
    if (s[2] == '+'):
        if requiresReturn:
            t = time.time()
            critTime = 2 #delay in seconds
            while(time.time() - t < critTime):
                #print(time.time()-t)
                if ser.in_waiting:
                    print('inWaiting'+str(ser.in_waiting))
                    line = ser.readline()
                    s = str(line)
                    return s[2]
        else:
            #works in case when we sent a char to printLine
            # and then waiting for user's response,
            # but the first returned character from Serial is '+'
            # so we ignore it and listen next
            return listen_serial(ser)
    if(requiresReturn):
        return '.'


if __name__ == "__main__":
    ser = serial.Serial(sg.get_port_arduino(), '9600')
    time.sleep(5)
    print(sg.get_port_arduino())
    print(listen_serial(ser))
    ser.close()
