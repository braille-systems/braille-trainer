from speech_synthesizer import text_to_speech
_ISTEST_ = True
if not _ISTEST_:
    import serial
    import time
    from serial_get_name import get_port_arduino
    from listen_serial import listen_serial
    from serial_hex import printLine as print_line
else:
    def listen_serial(ser_connection):
        return input()

    def print_line(text, ser_connection, menuID=-1):
        print("to braille cell: " + text)
        return listen_serial(0)


class Note(object):
    def __init__(self, text):
        self.text = text

    def __str__(self):
        return self.text

    def __repr__(self):
        return self.__str__()

def startApp(ser):
    notes = [['в какой город прибывает Дон Гуан? Введите ответ словом', 'мадрид', 'Правильный ответ - Мадрид'],
['какой композитор поставил оперу Пиковая дама? Введите ответ буквой. А: Чайковский, Б: Мусоргский, В: Бородин', 'а',
'Правильный ответ - А: в тысяча восемьсот девяностом году Пётр Ильич Чайковский написал во Флоренции оперу Пиковая дама, в том же году она была поставлена в Мариинском театре']
             ]
    for i in range(len(notes)):
        for j in range(3):
            notes[i][j] = Note(notes[i][j])
    i = 0
    if len(notes) == 0:
        text_to_speech('не найден файл текста')
        return
    text_to_speech((notes[i][0]).text)
    joystick_ans = print_line((notes[i][0]).text, ser, menuID='pushkin')
    if len(joystick_ans) == 0:
        if _ISTEST_:
            joystick_ans = (str(input()) + ' ')[0]  # technical substitution for testing
        else:
            joystick_ans = listen_serial(ser, "pushkin")


    while joystick_ans != 'l':
        if joystick_ans == 'd':
            if i == len(notes) - 1:
                i = 0
            else:
                i = i + 1

        if joystick_ans == 'u':
            if i == 0:
                i = len(notes) - 1
            else:
                i = i - 1

        if joystick_ans in 'du':
            print(notes[i][0])
            print('Отрывок ' + str(i))
            text_to_speech((notes[i][0]).text)
            joystick_ans = print_line((notes[i][0]).text, ser, menuID='pushkin')  # На ячейку текст текущей заметки

        if joystick_ans == 'r':
            pass  #process user's input, compare to notes[2], say true/false, TTS(notes[3])
            text_to_speech((notes[i][0]).text)
            joystick_ans = print_line((notes[i][0]).text, ser, menuID='pushkin')  # На ячейку текст текущей заметки

        if len(joystick_ans) == 0:
            if _ISTEST_:
                joystick_ans = (str(input()) + ' ')[0]  # technical substitution for testing
            else:
                joystick_ans = listen_serial(ser, "pushkin")

if __name__ == "__main__":
    if not _ISTEST_:
        ser = serial.Serial(get_port_arduino(), '9600')
        time.sleep(5)  # если мало "поспать", не работает
    else:
        ser = 'dummy_variable'
    startApp(ser)
    if not _ISTEST_:
        ser.close()
