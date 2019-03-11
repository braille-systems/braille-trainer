import serial
import time
from letter import LetterWidget
from audio import pronounce
from serial_hex import printLine
from listen_serial import listen_serial
from serial_get_name import get_port_arduino


def startApp(ser):
    """
    This is the Alphabet app for braille trainer.
    Designed to repeat all the letters of Braille alphabet.

    "ser" is an open Serial connection with Braille trainer
    (with Arduino board having '../arduino/printText/printText.ino' sketch loaded)
    
    1. Pronounces the letter aloud (not showing in a graphical window).
    First is 'a'
    Then prints to Braille cell.
    2. Waits for the joystick answer
    If 'r', goes to the next letter
    If 'u', repeats previous letter
    If 'd', repeats current
    If 'l', exits the application
    """
    ALF = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя'
    i = 0
    pronounce(ALF[i])
    printLine(ALF[i], ser)
    
    # joystick_ans = (str(input())+' ')[0] #technical substitution for testing
    joystick_ans = listen_serial(ser)
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
        printLine(ALF[i], ser)
        print('JOYSTICK ANS:')
        joystick_ans = listen_serial(ser)
        # joystick_ans = (str(input())+' ')[0]


if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  # если мало "поспать", не работает
    res = startApp(ser)
    ser.close()
