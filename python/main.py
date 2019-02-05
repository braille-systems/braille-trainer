import serial
import time
from edu import TestStep, LessonStep, Unit
from audio import playSoundByFilename
from serial_hex import printLine
#from joystick import listen_joystick
#from recognize import listen_symbol

def process_unit(unit):
    playSoundByFilename(unit.title)
    print(unit.title)
    #joystick_ans = listen_joystick()
    #while (joystick_ans != 'r'): #пока не велено зайти в юнит
        #joystick_ans = listen_joystick()
    ser = serial.Serial('COM7', '9600')
    time.sleep(5) # если мало "поспать", не работает
    for stp in unit: #для каждого шага юнита
        printLine(stp.bLine, ser)
        playSoundByFilename(stp.audio)
        print(stp.audio)
        if (unit.isTest()):
            while(stp.isRight()==false):
                s = 'п'
                #s=listen_symbol()
                if (s == stp.bLine): #если угадано
                    stp.setRight()
                    #надо произнести: Вы ответили верно
                else:
                    #надо произнести: Вы ответили неверно
                    pass
            #надо произнести: Вы ответили верно
    ser.close()
        

U1 = Unit(utype = 'lesson')
U1.title='audio/lesson1/0.wav'
less1 = LessonStep('audio/lesson1/1.wav', '', comment = 'Урок 1: а, б, о, п')
less2 = LessonStep('audio/lesson1/2.wav', 'а', comment = 'Потрогайте точку на поверхности тренажёра')
less3 = LessonStep('audio/lesson1/3.wav', 'б', comment = '')
U1.append(less1)
U1.append(less2)
U1.append(less3)

U2 = Unit(utype = 'test')
U2.title='audio/lesson1/0.wav'
test1 = LessonStep('lesson1.wav', 'A', comment = 'lesson1')
U2.append(test1)

process_unit(U1)

    
        
