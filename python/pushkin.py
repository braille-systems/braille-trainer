from speech_synthesizer import text_to_speech
from letter import LetterWidget
_ISTEST_ = False
if not _ISTEST_:
    import serial
    import time
    from serial_get_name import get_port_arduino
    from listen_serial import listen_serial
    from serial_hex import printLine as print_line
else:
    def listen_serial(ser_connection):
        return input()

    def print_line(text, ser_connection):
        print("to braille cell: " + text)


class Note(object):
    def __init__(self, text):
        self.text = text

    def __str__(self):
        return self.text

    def __repr__(self):
        return self.__str__()

def startApp(ser):
    notes = [[]]
    i = 0
    with open('pushkin.txt', encoding='utf-8') as file:
        for line in file:
            if (len(line) > 0) & (line != '\n'):
                notes[i].append(Note(line[:-2]))
            else:  # if empty line, start subnote
                if len(notes[i]) > 0:
                    notes.append([])
                    i += 1
    i = 0
    if len(notes) == 0:
        text_to_speech('не найден файл текста')
        return
    #text_to_speech('Маленькие трагедии')
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
            j = 1
            while joystick_ans in 'ur':  #printing current notes[i]
                text_to_speech((notes[i][j]).text)
                joystick_ans = print_line((notes[i][j]).text, ser, menuID='pushkin_line')  # На ячейку текст текущей заметки
                if joystick_ans == 'r':
                    if j < len(notes[i]):
                        j += 1
                    else:
                        text_to_speech("Конец отрывка")
                        break
                if len(joystick_ans) == 0:
                    if _ISTEST_:
                        joystick_ans = (str(input()) + ' ')[0]  # technical substitution for testing
                    else:
                        joystick_ans = listen_serial(ser, "pushkin_line")
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
