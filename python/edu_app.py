import sys
import serial
import time
from listen import listen_symbol
from letter import LetterWidget
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QThread
from edu import TestStep, LessonStep, Unit
from audio import playSoundByFilename, pronounce
from serial_hex import printLine, printBraille
from listen_serial import listen_serial
from serial_get_name import get_port_arduino
import speech_recognition as sr
from speech_synthesizer import text_to_speech as tts


class UnitProcessor(QThread):
    """
    Logic for Braille trainer's application - education
    _unit_menu(self, ser): processes the units menu 
    """
    
    def __init__(self, units, ser):
        QThread.__init__(self)
        self.lu = LetterWidget()
        self.lu.setLetter('')
        self.lu.show()
        self.units = units
        self.ser = ser
    
    def __del__(self):
        self.wait()
    
    def run(self):
        self._open_unit_menu(self.ser)
        print('closing')
        self.lu.close()
    
    def _unit_menu(self, ser):
        """
        Logic for units menu in educational app for Braille trainer.
        First, sets the unit to the first in the 'units' list.
        Plays its title aloud.
        Inside the 'while' (forever or until error) cycle:
        - waits for the joystick answer
            If 'r', returns the current unit. Assuming this unit
                will be launched after _unit_menu execution by invoking function!
            If 'u', goes to the previous unit (for first previous is the last)
            If 'd', goes to the next unit (for last next is the first)
            If 'l', returns None. Assuming the invoking function
                will launch the apps menu
        - Pronounces the app's title aloud
        
        "ser" is an open Serial connection with Braille trainer
        (with Arduino board having '../arduino/printText/printText.ino' sketch loaded).

        Every unit is either lesson or test (see edu.py for more information).

        """
        
        i = 0
        units = self.units
        unit = units[0]
        # playSoundByFilename(unit.title)
        tts(unit.title)
        print(unit.title)
        joystick_ans = listen_serial(ser)
        print(joystick_ans, i)
        while joystick_ans:
            print(joystick_ans)
            if joystick_ans == 'd':
                if i == len(units) - 1:
                    i = 0
                else:
                    i = i + 1
                unit = units[i]
                # playSoundByFilename(unit.title)
                tts(unit.title)
                print(i)
            if joystick_ans == 'u':
                if i == 0:
                    i = len(units) - 1
                else:
                    i = i - 1
                unit = units[i]
                #playSoundByFilename(unit.title)
                tts(unit.title)
                print(i)
            joystick_ans = listen_serial(ser)
            if joystick_ans == 'r':
                break
            if joystick_ans == 'l':
                return None
        return unit
    
    def _open_unit_menu(self, ser):
        """
        Opens unit menu and gives an opportunity to choose a lesson.
        """
        unit = self._unit_menu(ser)
        j = 0
        while unit != None:
            while 0 <= j < len(unit):  # для каждого шага юнита
                stp = unit[j]
                if isinstance(stp, LessonStep):
                    #playSoundByFilename(stp.audio)
                    tts(stp.comment)
                    print(stp.audio)
                    if(len(stp.bLine) == 7):
                        if(stp.bLine[0] == '%'):
                            printBraille(stp.bLine[1:7], ser)
                    elif (len(stp.bLine) != 0):
                        for chr in stp.bLine:
                            self.lu.setLetter(chr)
                            printLine(chr, ser)
                elif isinstance(stp, TestStep):
                    #playSoundByFilename(stp.audio)
                    tts(stp.comment)
                    print(stp.comment)
                    printLine(stp.bLine, ser)
                    self.sleep(3)
                    playSoundByFilename('audio/std_msg/signal.wav')
                    try:
                        answ = listen_symbol()
                    except BaseException:
                        print('ERROR caught in edu_app in open_unit_menu during listenSymbol')
                        answ = ''
                    i = 0
                    print('answ')
                    while answ != stp.bLine and i < 3:
                        print('err')
                        if answ == '':
                            playSoundByFilename('audio/std_msg/err_recognize.wav')
                        else:
                            playSoundByFilename('audio/std_msg/ans_incorrect.wav')
                        playSoundByFilename('audio/std_msg/signal.wav')
                        answ = listen_symbol()
                        print(answ)
                        i = i + 1
                    if answ == stp.bLine:
                        stp.setRight()
                        print('ssess')
                        playSoundByFilename('audio/std_msg/ans_correct.wav')
                    else:
                        playSoundByFilename('audio/std_msg/try_next_time.wav')
                    print(stp.bLine)
                    pronounce(stp.bLine)
                    print(stp.bLine)
                    self.lu.setLetter(stp.bLine)
                print('joystick')
                joystick_ans = listen_serial(ser)
                print(joystick_ans)
                while joystick_ans:
                    if joystick_ans == 'r':
                        j = j + 1
                        break
                    if joystick_ans == 'l':
                        j = j - 1
                        break
                    if joystick_ans == 'u':
                        break
                    if joystick_ans == 'd':
                        j = -1
                    joystick_ans = listen_serial(ser)
                    print(joystick_ans)
                printLine(' ', ser)
                self.lu.setLetter(' ')
            print('End lesson')
            print(j)
            if j == len(unit):
                if unit.utype == 'lesson':
                    playSoundByFilename('audio/std_msg/lesson_end.wav')
                else:
                    playSoundByFilename('audio/std_msg/test_end.wav')
            j = 0
            unit = self._unit_menu(ser)
        # if unit.isTest():
        #     while not stp.isRight():
        #         s = 'п'
        #         # s=listen_symbol()
        #         if s == stp.bLine:  # если угадано
        #             stp.setRight()
        #             # надо произнести: Вы ответили верно
        #         else:
        #             # надо произнести: Вы ответили неверно
        #             pass
        #     # надо произнести: Вы ответили верно


def initMenu():
    """
    Creating lessons, tests; filling them with proper steps.
    """

    U3 = Unit(utype='lesson')
    U3.title = 'Урок 3 - буквы А., Эм., У.'
    U3.append(LessonStep('','',comment='Буквы изучаются не по алфавиту. Сначала мы изучим более простые буквы - А., ЭМ., У. .'))
    U3.append(LessonStep('','а',comment='Потрогайте точку 1. Буква .А. обозначается точкой номер один'))
    U3.append(LessonStep('','м',comment='Буква .Эм. - это комбинация точек 1, 3 и 4'))
    U3.append(LessonStep('','ам',comment='а.м.'))
    U3.append(LessonStep('','ма',comment='м.а.'))
    U3.append(LessonStep('','мама',comment='мама'))
    U3.append(LessonStep('','у',comment='Последняя буква в этом уроке - буква .у. Попробуйте самостоятельно определить на ощупь номера точек, образующих букву у'))
    U3.append(LessonStep('','у',comment='Правильный ответ: буква .у. - это точки 1, 3 и 6'))
    U3.append(LessonStep('','ау',comment='а.у.'))
    U3.append(LessonStep('','му',comment='м.у.'))
    U3.append(LessonStep('','ум',comment='у.м.'))
    U3.append(LessonStep('','ума',comment='у.м.а.'))
    U3.append(LessonStep('','маму',comment='маму'))
    U3.append(LessonStep('','',comment='конец урока. Спасибо за терпение'))

    U1 = Unit(utype='lesson')
    U1.title = 'audio/live/lessons/1/lesson1Dots.wav'
    less1 = LessonStep('audio/live/lessons/1/2Encodes.wav', '', comment='Шрифт Брайля кодирует кажду букву алфавита комбинацией точек в ячейке Брайля')
    less2 = LessonStep('audio/live/lessons/1/3Consists.wav', '', comment='')
    less3 = LessonStep('audio/live/lessons/1/4Enum.wav', '', comment='')
    less4 = LessonStep('audio/live/lessons/1/5nowTouch.wav', '', comment='')
    less5 = LessonStep('audio/live/lessons/1/6touch1.wav', '%100000', comment='Потрогайте точку 1')
    less6 = LessonStep('audio/live/lessons/1/7touch2.wav', '%010000', comment='Потрогайте точку 2')
    less7 = LessonStep('audio/live/lessons/1/8touch3.wav', '%001000', comment='Потрогайте точку 3')
    less8 = LessonStep('audio/live/lessons/1/9touch4.wav', '%000100', comment='Потрогайте точку 4')
    less9 = LessonStep('audio/live/lessons/1/10touch5.wav', '%000010', comment='Потрогайте точку 5')
    less10 = LessonStep('audio/live/lessons/1/11touch6.wav', '%000001', comment='Потрогайте точку 6')
    
    U1.append(less1)
    U1.append(less2)
    U1.append(less3)
    U1.append(less4)
    U1.append(less5)
    U1.append(less6)
    U1.append(less7)
    U1.append(less8)
    U1.append(less9)
    U1.append(less10)

    U2 = Unit(utype='lesson')
    U2.title = 'audio/live/lessons/2/lesson2amu.wav'
    less1 = LessonStep('audio/live/lessons/2/2order.wav', '', comment='')
    less2 = LessonStep('audio/live/lessons/2/3remember.wav', '', comment='')
    less3 = LessonStep('audio/live/lessons/2/4whatAboutWords.wav', '', comment='')
    less4 = LessonStep('audio/live/lessons/2/5goToLetters.wav', '', comment='')
    less5 = LessonStep('audio/live/lessons/2/6a.wav', 'а', comment='')
    
    U2.append(less1)
    U2.append(less2)
    U2.append(less3)
    U2.append(less4)
    U2.append(less5)
    #U2.append(less2)
    
    U1a = Unit(utype='lesson')
    U1a.title = 'audio/lesson1v2/title.wav'
    less1 = LessonStep('audio/lesson1v2/l1s1.wav', 'а', comment='Потрогайте точку на поверхности тренажёра')
    less2 = LessonStep('audio/lesson1v2/l1s2.wav', 'б', comment='Буква б, две точки')
    less3 = LessonStep('audio/lesson1v2/l1s3.wav', ' ', comment='Прочитайте про себя слоги.')
    less4 = LessonStep('audio/lesson1v2/l1s4.wav', 'аб', comment='АБ')
    less5 = LessonStep('audio/lesson1v2/l1s5.wav', 'ба', comment='БА')
    less6 = LessonStep('audio/lesson1v2/l1s6.wav', 'о', comment='Буква О - три точки: номер 1, 3, 5')
    less7 = LessonStep('audio/lesson1v2/l1s7.wav', ' ', comment='Прочитайте про себя слоги и слова.')
    less8 = LessonStep('audio/lesson1v2/l1s8.wav', 'бо', comment='БО')
    less9 = LessonStep('audio/lesson1v2/l1s9.wav', 'об', comment='ОБ')
    less10 = LessonStep('audio/lesson1v2/l1s10.wav', 'боб', comment='БОБ')
    U1a.append(less1)
    U1a.append(less2)
    U1a.append(less3)
    U1a.append(less4)
    U1a.append(less5)
    U1a.append(less6)
    U1a.append(less7)
    U1a.append(less8)
    U1a.append(less9)
    U1a.append(less10)
    
    
    Test1 = Unit(utype='test')
    Test1.title = 'audio/test1/title.wav'
    less1 = TestStep('audio/test1/1.wav', 'а',
                     comment='Потрогайте букву на поверхности тренажёра. После сигнала произнесите её вслух')
    less2 = TestStep('audio/test1/1.wav', 'б',
                     comment='Потрогайте букву на поверхности тренажёра. После сигнала произнесите её вслух')
    less3 = TestStep('audio/test1/1.wav', 'о',
                     comment='Потрогайте букву на поверхности тренажёра. После сигнала произнесите её вслух')
    less4 = TestStep('audio/test1/1.wav', 'п',
                     comment='Потрогайте букву на поверхности тренажёра. После сигнала произнесите её вслух')
    Test1.append(less1)
    Test1.append(less2)
    Test1.append(less3)
    Test1.append(less4)
    
    return [U3, U1, U2, U1a, Test1]


def startApp(ser):
    app = QApplication(sys.argv)
    thread1 = UnitProcessor(initMenu(), ser)
    thread1.start()
    return app.exec_()


if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(3)  # если мало "поспать", не работает
    res = startApp(ser)
    ser.close()
    sys.exit(res)
