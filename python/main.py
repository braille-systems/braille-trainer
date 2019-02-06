import sys
import serial
from letter import LetterWidget
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QThread
from edu import TestStep, LessonStep, Unit
from audio import playSoundByFilename
from serial_hex import printLine
from joystick import listen_joystick


class UnitProcessor(QThread):

    def __init__(self, unit):
        QThread.__init__(self)
        self.lu = LetterWidget()
        self.lu.setLetter('')
        self.lu.show()
        self.unit = unit

    def __del__(self):
        self.wait()
        self.lu.close()

    def run(self):
        unit = self.unit
        ser = serial.Serial('COM7', '9600')
        self.sleep(5)  # если мало "поспать", не работает
        playSoundByFilename(unit.title)
        print(unit.title)
        joystick_ans = listen_joystick(ser)
        while joystick_ans != 'r':  # пока не велено зайти в юнит
            print(joystick_ans)
            joystick_ans = listen_joystick(ser)
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
    U1.title = 'audio/lesson1/0.wav'
    less1 = LessonStep('audio/lesson1/1.wav', '', comment='Урок 1: а, б, о, п')
    less2 = LessonStep('audio/lesson1/2.wav', 'а', comment='Потрогайте точку на поверхности тренажёра')
    less3 = LessonStep('audio/lesson1/3.wav', 'б', comment='')
    U1.append(less1)
    U1.append(less2)
    U1.append(less3)

    U2 = Unit(utype='test')
    U2.title = 'audio/lesson1/0.wav'
    test1 = LessonStep('lesson1.wav', 'A', comment='lesson1')
    U2.append(test1)
    thread1 = UnitProcessor(U1)
    thread1.start()
    sys.exit(app.exec_())
