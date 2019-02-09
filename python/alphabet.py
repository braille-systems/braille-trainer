import serial
import time
from letter import LetterWidget
from audio import pronounce
from serial_hex import printLine
from joystick import listen_joystick
from serial_get_name import get_port_arduino

def startApp(ser):
    ALF = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя'
    i = 0
    pronounce(ALF[i])
    printLine(ALF[i], ser)
 
    #joystick_ans = (str(input())+' ')[0]
    joystick_ans = listen_joystick(ser)
    while joystick_ans != 'l':
        print(joystick_ans)
        if joystick_ans == 'd':
            if i == len(ALF) - 1:
                i = 0
            else:
                i = i + 1
        if joystick_ans == 'u':
            if i == 0:
                i = len(ALF) - 1
            else:
                i = i - 1
        
        pronounce(ALF[i])        
        printLine(ALF[i],ser)
        print('JOYSTICK ANS:')
        joystick_ans = listen_joystick(ser)
        #joystick_ans = (str(input())+' ')[0]
if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  # если мало "поспать", не работает
    res = startApp(ser)
    ser.close()
