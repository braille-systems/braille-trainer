import sys
import serial
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

        i = 0
        unit = self.units[0]
        playSoundByFilename(unit.title)
        print(unit.title)
        # joystick_ans = listen_joystick(ser)
        joystick_ans = listen_joystick(ser)
        while joystick_ans:  # меню выбора Юнита
            print(joystick_ans)
            if joystick_ans == 'd':
                if i == len(self.units) - 1:
                    i = 0
                else:
                    i = i + 1
                unit = self.units[i]
                print(i)
            if joystick_ans == 'u':
                if i == 0:
                    i = len(self.units) - 1
                else:
                    i = i - 1
                unit = self.units[i]
                print(i)
            joystick_ans = listen_joystick(ser)
            if joystick_ans == 'r':
                break
        print(joystick_ans, i)

        for stp in unit:  # для каждого шага юнита
            self.lu.setLetter(stp.bLine)
            printLine(stp.bLine, ser)
            playSoundByFilename(stp.audio)
            print(stp.audio)
            joystick_ans = listen_joystick(ser)
            while joystick_ans != 'r':  # пока не велено зайти в юнит
                print(joystick_ans)
                joystick_ans = listen_joystick(ser)
            if unit.isTest():
                while not stp.isRight():
                    s = 'п'
                    # s=listen_symbol()
                    if s == stp.bLine:  # если угадано
                        stp.setRight()
                        # надо произнести: Вы ответили верно
                    else:
                        # надо произнести: Вы ответили неверно
                        pass
                # надо произнести: Вы ответили верно

        ser.close()


if __name__ == "__main__":
    app = QApplication(sys.argv)

    U1 = Unit(utype='lesson')
    U1.title = 'audio/lesson1/1.wav'
    less1 = LessonStep('audio/lesson1/1.wav', 'а', comment='Потрогайте точку на поверхности тренажёра')
    less2 = LessonStep('audio/lesson1/2.wav', 'б', comment='Буква б, две точки')
    U1.append(less1)
    U1.append(less2)

    U2 = Unit(utype='lesson')
    U2.title = 'audio/lesson1/1.wav'
    less12 = LessonStep('audio/lesson1/2.wav', 'а', comment='Потрогайте точку на поверхности тренажёра')
    less22 = LessonStep('audio/lesson1/1.wav', 'б', comment='Буква б, две точки')
    U2.append(less12)
    U2.append(less22)

    U3 = Unit(utype='lesson')
    U3.title = 'audio/lesson1/1.wav'
    less13 = LessonStep('audio/lesson1/1.wav', 'а', comment='Потрогайте точку на поверхности тренажёра')
    less23 = LessonStep('audio/lesson1/2.wav', 'б', comment='Буква б, две точки')
    U3.append(less13)
    U3.append(less23)

    thread1 = UnitProcessor([U1, U2, U3])
    thread1.start()
    sys.exit(app.exec_())
