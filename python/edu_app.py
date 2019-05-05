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
                tts(unit.title)
                print(i)
            if joystick_ans == 'u':
                if i == 0:
                    i = len(units) - 1
                else:
                    i = i - 1
                unit = units[i]
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
                joystick_ans = listen_serial(ser, 'units_tests')
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
                    joystick_ans = listen_serial(ser, 'units_tests')
                    print(joystick_ans)
                printLine(' ', ser)
                self.lu.setLetter(' ')
            print('End lesson')
            print(j)
            if j == len(unit):
                if unit.utype == 'lesson':
                    tts("Поздравляем. Вы прошли урок!")
                else:
                    tts("Поздравляем. Вы прошли тест!")
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
    U = []
    for i in range(5):
        U.append(0)
    U[0] = Unit(utype='lesson')
    U[0].title = 'Урок ноль - историческая справка.'
    # U[0].append(LessonStep('', '',comment='До определённого времени уделом слепого было нищенство - считалось, что недуг дан от Бога и ему нужно покориться.'))
    U[0].append(LessonStep('', '',
                         comment='В эпоху Просвещения идеи гуманизма привели к осознанию в Европе необходимости образования слепых.'))
    U[0].append(LessonStep('', '',
                         comment='Первую единую азбуку для незрячих разработал Валентин Гаюи на рубеже восемнадцатого-девятнадцатого веков.'))
    U[0].append(LessonStep('', '',
                         comment='Валентин Гаюи родился в 1745 году в семье бедного ткача, но получил хорошее образование и стал чиновноком. Гаюи, увлекшись идеями просветителей, разработал линейный рельефный шрифт, которому стал обучать слепых. Скоро школа Гаюи приобрела известность, он обучил более шестидесяти человек, разработал специальный прибор для линейного письма - деревянный станок с горизонтально натянутыми струнами. Гаюи разработал первые карты и глобус для слепых.'))
    U[0].append(LessonStep('', '',
                         comment='Более ста лет на станках, созданных Гаюи, печаталась литература для незрячих. Были и аналоги, в том числе точечный шрифт Барбье, но они не пользовались такой популярностью.'))
    U[0].append(LessonStep('', '',
                         comment='Заслуга создания самой совершенной точечной системы для письма принадлежит Луи Брайлю.'))
    U[0].append(LessonStep('', '',
                         comment='Луи Брайль родился в 1809 году близ Парижа в семье шорника. В три года потерял зрение в результате несчастного случая. Окончил Парижский институт слепых, затем стал там преподавать.'))
    U[0].append(LessonStep('', '',
                         comment='Десять лет Луи Брайль разрабатывал свою систему, которая сначала не получила широкого признания. Лишь после смерти создателя систему оценили.'))
    U[0].append(LessonStep('', '',
                         comment='Шеститочие, положенное в основу системы, хорошо приспособлено для осязания. Шести точек как раз достаточно для изображения букв и знаков препинания, а больше не поместилось бы под подушечкой пальца.'))
    U[0].append(LessonStep('', '',
                         comment='По сей день шрифтом Брайля печатаются книги, ему учат во всех странах. Появились печатные машинки и дисплеи Брайля. Есть брайлевские таблицы и графики, ноты по Брайлю. Мы желаем Вам успешно освоить азбуку Брайля.'))

    U[1] = Unit(utype='lesson')
    U[1].title = 'Урок 1 - знакомство с шеститочием Брайля.'
    U[1].append(LessonStep('', '%111111', comment='Шрифт Брайля кодирует кажду букву комбинацией точек в ячейке Брайля. Точки расположены в два столбца, по три точки в столбце'))
    U[1].append(LessonStep('', '%100000', comment='Для удобства точки пронумерованы от одного до шести. Точка 1 в левом верхнем углу, ознакомьтесь с ней'))
    U[1].append(LessonStep('', '%010000', comment='Дальше вниз идут точки 2 и 3. Потрогайте точку 2 - среднюю в левом столбце'))
    U[1].append(LessonStep('', '%001000', comment='Точка 3 - нижняя в левом столбце'))
    U[1].append(LessonStep('', '%000100', comment='В правом столбце сверху вниз идут точки 4, 5, 6. Сейчас выведена точка 4.'))
    U[1].append(LessonStep('', '%000010', comment='Точка 5.'))
    U[1].append(LessonStep('', '%000001', comment='Точка 6.'))
    U[1].append(LessonStep('', '%100000', comment='Повторим точки заново: точка номер 1.'))
    U[1].append(LessonStep('', '%010000', comment='Точка 2'))
    U[1].append(LessonStep('', '%001000', comment='а это какая точка? Ответ на следующем шаге.'))
    U[1].append(LessonStep('', '%001000', comment='Конечно же, это точка 3.'))
    U[1].append(LessonStep('', '%000001', comment='Точка 6'))
    U[1].append(LessonStep('', '%000010', comment='Точка 5'))
    U[1].append(LessonStep('', '%000100', comment='Точка 4'))

    #U[2] = Unit(utype='test')
    #U[2].title = 'Тест 1 - номера точек'

    U[2] = Unit(utype='lesson')
    U[2].title = 'Урок 2 - буквы А., Эм., У.'
    U[2].append(LessonStep('', '',
                         comment='Буквы изучаются не по алфавиту. Сначала мы изучим более простые буквы - А., ЭМ., У. .'))
    U[2].append(LessonStep('', 'а', comment='Потрогайте точку 1. Буква .А. обозначается точкой номер один'))
    U[2].append(LessonStep('', 'м', comment='Буква .Эм. - это комбинация точек 1, 3 и 4'))
    U[2].append(LessonStep('', 'ам', comment='а.м.'))
    U[2].append(LessonStep('', 'ма', comment='м.а.'))
    U[2].append(LessonStep('', 'мама', comment='мама'))
    U[2].append(LessonStep('', 'у',
                         comment='Последняя буква в этом уроке - буква .у. Попробуйте самостоятельно определить на ощупь номера точек, образующих букву у'))
    U[2].append(LessonStep('', 'у', comment='Правильный ответ: буква .у. - это точки 1, 3 и 6'))
    U[2].append(LessonStep('', 'ау', comment='а.у.'))
    U[2].append(LessonStep('', 'му', comment='м.у.'))
    U[2].append(LessonStep('', 'ум', comment='у.м.'))
    U[2].append(LessonStep('', 'ума', comment='у.м.а.'))
    U[2].append(LessonStep('', 'маму', comment='маму'))
    U[2].append(LessonStep('', '', comment='конец урока. Спасибо за терпение'))

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

    return [U[0], U[1], U[2], U1a, Test1]


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
