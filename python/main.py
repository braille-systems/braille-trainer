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
        unit = self._unit_menu(ser)
        j = 0
        while j < len(unit):  # для каждого шага юнита
            stp = unit[j]
            self.lu.setLetter(stp.bLine)
            printLine(stp.bLine, ser)
            playSoundByFilename(stp.audio)
            print(stp.audio)
            joystick_ans = listen_joystick(ser)
            while joystick_ans:
                if joystick_ans == 'r':
                    j = j + 1
                    break
                if joystick_ans == 'l':
                    j = j - 1
                    break
                joystick_ans = listen_joystick(ser)
                if joystick_ans == 'u':
                    break
                if joystick_ans == 'd':
                    self._unit_menu(ser)

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
    U1.title = 'audio/lesson1/1.wav'
    less1 = LessonStep('audio/lesson1/1.wav', 'а', comment='Потрогайте точку на поверхности тренажёра')
    less2 = LessonStep('audio/lesson1/2.wav', 'б', comment='Буква б, две точки')
    U1.append(less1)
    U1.append(less2)

    U2 = Unit(utype='lesson')
    U2.title = 'audio/lesson1/2.wav'
    less12 = LessonStep('audio/lesson1/2.wav', 'а', comment='Потрогайте точку на поверхности тренажёра')
    less22 = LessonStep('audio/lesson1/1.wav', 'б', comment='Буква б, две точки')
    U2.append(less12)
    U2.append(less22)

    U3 = Unit(utype='lesson')
    U3.title = 'audio/lesson1/3.wav'
    less13 = LessonStep('audio/lesson1/1.wav', 'а', comment='Потрогайте точку на поверхности тренажёра')
    less23 = LessonStep('audio/lesson1/2.wav', 'б', comment='Буква б, две точки')
    U3.append(less13)
    U3.append(less23)

    thread1 = UnitProcessor([U1, U2, U3])
    thread1.start()
    sys.exit(app.exec_())
