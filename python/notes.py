import time
import serial
from audio import playSoundByFilename
from serial_get_name import get_port_arduino
from listen_serial import listen_serial
from serial_hex import braille_to_char
from serial_hex import printLine


class Note(object):
    def __init__(self, title, body):
        self.title = title
        self.body = body

    def __str__(self):
        return self.title + " " + self.body

    def __repr__(self):
        return self.__str__()

    def new_note(title, body):
        with open('saved_notes.txt', "a", encoding="utf-8") as file:
            file.write("\n" + title + "\\" + body)
            playSoundByFilename('')  # Заметка сохранена
            print('Заметка сохранена')
            return Note(title, body)

    def delete_note(title, body):
        pass


def startApp(ser):
    notes = ["новая заметка"]
    with open('saved_notes.txt', encoding='utf-8') as file:
        for line in file:
            temp = line.split("\\")  # title and body
            if len(temp) == 2:
                notes.append(Note(temp[0], temp[1]))
    print(notes)
    # joystick_ans = (str(input())+' ')[0] #technical substitution for testing
    i = 0
    joystick_ans = listen_serial(ser)
    while joystick_ans != 'l':

        if joystick_ans == 'd':
            if i == len(notes) - 1:
                i = 0
                print('Новая заметка')
                playSoundByFilename('')  # Новая заметка
            else:
                i = i + 1
                print('Заметка ' + str(i))
                printLine(notes[i - 1].title if i != 1 else notes[0], ser)  # На ячейку имя предыдущей заметки
                playSoundByFilename('')  # Заметка номер [i]
                printLine(notes[i].title, ser)  # На ячейку имя текущей заметки

        if joystick_ans == 'u':
            if i == 0:
                i = len(notes) - 1
            else:
                i = i - 1
            if i == 0:
                print('Новая заметка')
                playSoundByFilename('')  # Новая заметка
            else:
                print('Заметка ' + str(i))
                printLine(notes[i+1].title if i != len(notes)-1 else notes[0], ser)  # На ячейку имя предыдущей заметки
                playSoundByFilename('')  # Заметка номер [i]
                printLine(notes[i].title, ser)  # На ячейку имя текущей заметки

        if joystick_ans == 'r':
            if i == 0:
                title = ""
                body = ""
                playSoundByFilename('audio/live/notes/notesEnterTitle.wav')  # Введите название
                joy_keyboard_ans = ""
                while joy_keyboard_ans != "r":
                    joy_keyboard_ans = listen_serial(ser)
                    if len(joy_keyboard_ans) == 6:
                        title = title + braille_to_char(joy_keyboard_ans)
                print('Название создаваемой заметки' + title)
                joy_keyboard_ans = ""
                while joy_keyboard_ans != "r":
                    joy_keyboard_ans = listen_serial(ser)
                    if len(joy_keyboard_ans) == 6:
                        body = body + braille_to_char(joy_keyboard_ans)
                print('Тело создаваемой заметки: ' + body)
                i = len(notes)
                notes.append(Note.new_note(title, body))
            else:
                playSoundByFilename('audio/live/notes/notesTitle.wav')  # Название заметки
                printLine(notes[i].title, ser)
                playSoundByFilename('audio/live/notes/notesBody.wav')  # Тело заметки
                printLine(notes[i].body, ser)
                playSoundByFilename('audio/live/notes/notesAfter.wav')
                # Чтобы удалить заметку, нажмите вверх; чтобы выйти в меню заметок, нажмите влево

        joystick_ans = listen_serial(ser)
        # joystick_ans = (str(input())+' ')[0]
    pass


if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  # если мало "поспать", не работает
    res = startApp(ser)
    ser.close()
