import time
import serial
from audio import playSoundByFilename, pronounce
from serial_get_name import get_port_arduino
from listen_serial import listen_serial
from serial_hex import braille_to_char
from serial_hex import printLine
from speech_synthesizer import text_to_speech

class Note(object):
    def __init__(self, text):
        self.text = text

    def __str__(self):
        return self.text

    def __repr__(self):
        return self.__str__()

    def add_to_note(note_number, new_text):
        lines = []
        with open('saved_notes.txt', "r", encoding="utf-8") as file:
            for line in file:
                lines.append(line[:-2])
        with open('saved_notes.txt', "w", encoding="utf-8") as file:
            for i in range(len(lines)):
                if i != note_number - 1:
                    file.write(lines[i] + "\\" + "\n")
                else:
                    file.write(lines[i] + new_text + "\\" + "\n")
        playSoundByFilename('audio/notes/notesAdded.wav')
        print("Заметка дополнена")

    def new_note(text):
        with open('saved_notes.txt', "a", encoding="utf-8") as file:
            file.write(text + "\\" + "\n")
            playSoundByFilename('audio/notes/notesSaved.wav')  # Заметка сохранена
            print('Заметка сохранена')
            return Note(text)

    def delete_note(note_number):
        lines = []
        with open('saved_notes.txt', "r", encoding="utf-8") as file:
            for line in file:
                lines.append(line[:-2])
        with open('saved_notes.txt', "w", encoding="utf-8") as file:
            for i in range(len(lines)):
                if i != note_number - 1:
                    file.write(lines[i] + "\\" + "\n")
            print("Заметка удалена")
            playSoundByFilename('audio/notes/notesDeleted.wav')


def startApp(ser):
    notes = ["новая заметка"]
    with open('saved_notes.txt', encoding='utf-8') as file:
        for line in file:
            notes.append(Note(line[:-2]))
    print(notes)
    # joystick_ans = (str(input())+' ')[0] #technical substitution for testing
    i = 0
    text = ''
    text_to_speech('Если Вы хотите создать новую заметку, нажмите вправо. Чтобы пролистать список заметок, нажмите вниз или вверх')
    # playSoundByFilename('audio/notes/notesStart.wav')
    joystick_ans = listen_serial(ser)
    while joystick_ans != 'l':
        if len(joystick_ans) == 6:
            letter = braille_to_char(joystick_ans)
            if letter in 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя' and len(letter) != 0:
                pronounce(letter)
            printLine(letter, ser)
            text = text + letter
            print(text)

        if joystick_ans == 'd':
            if i == len(notes) - 1:
                i = 0
                print('Новая заметка')
                playSoundByFilename('audio/notes/notesNew.wav')  # Новая заметка
            else:
                i = i + 1
                print(notes[i])
                print('Заметка ' + str(i))
                printLine(notes[i].text, ser)  # На ячейку текст текущей заметки

        if joystick_ans == 'u':
            if i == 0:
                i = len(notes) - 1
            else:
                i = i - 1
            if i == 0:
                print('Новая заметка')
                playSoundByFilename('audio/notes/notesNew.wav')  # Новая заметка
            else:
                print('Заметка ' + str(i))
                printLine(notes[i].text, ser)  # На ячейку текст текущей заметки

        if joystick_ans == 'r':
            if text != '':
                print('Текст созданной заметки: ' + text)
                i = len(notes)
                notes.append(Note.new_note(text))
                text = ""
            else:
                if i == 0:
                    text = ""
                    playSoundByFilename('audio/notes/notesEnterTitle.wav')  # Введите текст
                    joy_keyboard_ans = ""
                    while joy_keyboard_ans != "r":
                        joy_keyboard_ans = listen_serial(ser)
                        if len(joy_keyboard_ans) == 6:
                            letter = braille_to_char(joy_keyboard_ans)
                            text = text + letter
                            if letter in 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя' and len(letter) != 0:
                                pronounce(letter)
                            printLine(letter, ser)
                    print('Текст созданной заметки: ' + text)
                    i = len(notes)
                    notes.append(Note.new_note(text))
                    text = ""
                else:
                    playSoundByFilename('audio/notes/notesActions.wav')
                    joy_keyboard_ans = listen_serial(ser)
                    while joy_keyboard_ans != 'l':
                        if joy_keyboard_ans == 'd':
                            Note.delete_note(i)
                            print(notes[i].text)
                            del notes[i]
                            i = i - 1
                            break
                        if joy_keyboard_ans == 'r':
                            joy_ans = listen_serial(ser)
                            new_text = ""
                            while joy_ans != 'r':
                                if len(joy_ans) == 6:
                                    letter = braille_to_char(joy_ans)
                                    if letter in 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя' and len(letter) != 0:
                                        pronounce(letter)
                                    printLine(letter, ser)
                                    new_text = new_text + letter
                                joy_ans = listen_serial(ser)
                            print(new_text)
                            notes[i].text = notes[i].text + new_text
                            Note.add_to_note(i, new_text)
                            break
                        joy_keyboard_ans = listen_serial(ser)

        joystick_ans = listen_serial(ser)
        # joystick_ans = (str(input())+' ')[0]
    pass


if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  # если мало "поспать", не работает
    res = startApp(ser)
    ser.close()