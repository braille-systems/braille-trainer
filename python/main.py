import sys
import serial
from listen import listen_symbol
from letter import LetterWidget
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QThread
from edu import TestStep, LessonStep, Unit
from audio import playSoundByFilename
from serial_hex import printLine
from joystick import listen_joystick
from serial_get_name import get_port_arduino

class UnitProcessor(QThread):

    def __init__(self, units):
        QThread.__init__(self)
        self.lu = LetterWidget()
        self.lu.setLetter('')
        self.lu.show()
        self.units = units

    def __del__(self):
        self.wait()
        self.lu.close()

    def run(self):
        ser = serial.Serial(get_port_arduino(), '9600')
        self.sleep(5)  # если мало "поспать", не работает
        self._open_unit_menu(ser)
        print('closing')
        ser.close()

    def _unit_menu(self, ser):
        """Units menu"""
        i = 0
        units = self.units
        unit = units[0]
        playSoundByFilename(unit.title)
        print(unit.title)
        joystick_ans = listen_joystick(ser)
        print(joystick_ans, i)
        while joystick_ans:
            print(joystick_ans)
            if joystick_ans == 'd':
                if i == len(units) - 1:
                    i = 0
                else:
                    i = i + 1
                unit = units[i]
                playSoundByFilename(unit.title)
                print(i)
            if joystick_ans == 'u':
                if i == 0:
                    i = len(units) - 1
                else:
                    i = i - 1
                unit = units[i]
                playSoundByFilename(unit.title)
                print(i)
            joystick_ans = listen_joystick(ser)
            if joystick_ans == 'r':
                break
        return unit

    def _open_unit_menu(self, ser):
        """Opens unit menu and gives a possibility to choose a lesson"""
        while True:
            unit = self._unit_menu(ser)
            j = 0
            while 0 <= j < len(unit):  # для каждого шага юнита
                stp = unit[j]
                if isinstance(stp, LessonStep):
                    for chr in stp.bLine:
                        self.lu.setLetter(chr)
                        printLine(chr, ser)
                    playSoundByFilename(stp.audio)
                    print(stp.audio)
                elif isinstance(stp, TestStep):
                    playSoundByFilename(stp.audio)
                    print(stp.audio)
                    printLine(stp.bLine, ser)
                    playSoundByFilename('audio/std_msg/signal.wav')
                    try:
                        answ = listen_symbol()
                    except BaseError:
                        print('ERROR!!!')
                    i = 0
                    print('answ')
                    while answ != stp.bLine and i<3:
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
                    playSoundByFilename('audio/'+str(ord(stp.bLine)-ord('а')+1)+'.wav')
                    self.lu.setLetter(stp.bLine)

                joystick_ans = listen_joystick(ser)
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
                         unit = self._unit_menu(ser)
                         j = 0
                    joystick_ans = listen_joystick(ser)
                    print(joystick_ans)
                printLine(' ', ser)
                self.lu.setLetter(' ')
            print('End lesson')
            print(j)
            if(j == len(unit)):
                if(unit.utype == 'lesson'):
                    playSoundByFilename('audio/std_msg/lesson_end.wav')
                else:
                    playSoundByFilename('audio/std_msg/test_end.wav')
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


if __name__ == "__main__":
    app = QApplication(sys.argv)
    U1 = Unit(utype='lesson')
    U1.title = 'audio/lesson1v2/title.wav'
    less1 = LessonStep('audio/lesson1v2/l1s1.wav', 'а', comment='Потрогайте точку на поверхности тренажёра')
    less2 = LessonStep('audio/lesson1v2/l1s2.wav', 'б', comment='Буква б, две точки')
    less3 = LessonStep('audio/lesson1v2/l1s3.wav', ' ', comment='Прочитайте про себя слоги.')
    less4 = LessonStep('audio/lesson1v2/l1s4.wav', 'аб', comment='АБ')
    less5 = LessonStep('audio/lesson1v2/l1s5.wav', 'ба', comment='БА')
    less6 = LessonStep('audio/lesson1v2/l1s6.wav', 'о', comment='Буква О - три точки: номер 1, 3, 5')
    less7 = LessonStep('audio/lesson1v2/l1s7.wav', '', comment='Прочитайте про себя слоги и слова.')
    less8 = LessonStep('audio/lesson1v2/l1s8.wav', 'бо', comment='БО')
    less9 = LessonStep('audio/lesson1v2/l1s9.wav', 'об', comment='ОБ')
    less10 = LessonStep('audio/lesson1v2/l1s10.wav', 'боб', comment='БОБ')
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
    Test1 = Unit(utype='test')
    Test1.title = 'audio/test1/title.wav'
    less1 = TestStep('audio/test1/1.wav', 'е', comment='Потрогайте букву на поверхности тренажёра. После сигнала произнесите её вслух')
    Test1.append(less1)
    thread1 = UnitProcessor([U1, Test1])
    thread1.start()         
    sys.exit(app.exec_())
