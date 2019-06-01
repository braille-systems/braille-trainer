import edu_app
import notes
import alphabet
import clock
import calculator
import settings
import serial
import blitz
import pushkin
from audio import playSoundByFilename
from listen_serial import listen_serial
import time
from serial_get_name import get_port_arduino
from serial_hex import braille_to_char
from serial_hex import printLine
from audio import playSoundByFilename, pronounce
from speech_synthesizer import text_to_speech

def _app_menu(ser, apps):
    """
    Applications menu for Braille trainer.

    "ser" is an open Serial connection with Braille trainer
    (with Arduino board having '../arduino/printText/printText.ino' sketch loaded).

    "apps" is a list of apps (such as alphabet app) for braille trainer.

    First, sets the app to the first in the 'apps' list.
    Plays its title aloud.
    Inside the 'while' (forever or until error) cycle:
    - waits for the joystick answer
        If 'r', launches the app
        If 'u', goes to the previous app (for first previous is the last)
        If 'd', goes to the next app (for last next is the first)
        If 'l', does nothing
    - Pronounces the app's title aloud
    """
    i = 0
    app = apps[0]
    text_to_speech(app[2])
    #playSoundByFilename(app[0])
    print(app[0])
    joystick_ans = listen_serial(ser, 'main')
    print(joystick_ans, i)
    text = ''
    while joystick_ans:
        print(joystick_ans)
        if len(joystick_ans) == 6:
            letter = braille_to_char(joystick_ans)
            if len(letter) != 0:
                text_to_speech(letter)
            else:
                text_to_speech("неизвестный символ")
            printLine(letter, ser)
            text += letter
            print(text)
        if joystick_ans == 'l':
            text = text[:-1]
            text_to_speech(text)
        if joystick_ans == 'd':
            text = ''
            if i == len(apps) - 1:
                i = 0
            else:
                i = i + 1
            app = apps[i]
            text_to_speech(app[2])
            #playSoundByFilename(app[0])
            print(i)
        if joystick_ans == 'u':
            text = ''
            if i == 0:
                i = len(apps) - 1
            else:
                i = i - 1
            app = apps[i]
            text_to_speech(app[2])
            #playSoundByFilename(app[0])
            
            print(i)
        joystick_ans = listen_serial(ser, 'main')
        if joystick_ans == 'r':
            if text != '':
                with open('saved_notes.txt', "a", encoding="utf-8") as file:
                    file.write(text + "\\" + "\n")
                    text_to_speech('Заметка сохранена')
                    # playSoundByFilename('audio/notes/notesSaved.wav')  # Заметка сохранена
                    print('Заметка сохранена')
            else:
                break
    return app


if __name__ == "__main__":
    apps = [
        ['', pushkin.startApp, 'Пушкин. Маленькие Трагедии. Отрывки'],
        ['audio/apps/eduApp.wav', edu_app.startApp, 'уроки'],
        ['audio/apps/notesApp.wav', notes.startApp, 'заметки'],
        ['audio/apps/alphabetApp.wav', alphabet.startApp, 'азбука'],
        ['audio/apps/clocksApp.wav', clock.startApp, 'часы'],
        ['audio/apps/calculatorApp.wav', calculator.startApp, 'калькулятор'],
        ['~', blitz.startApp, 'блиц-опрос'],
        ['', settings.startApp, 'настройки'],
        ]
    i = 0

    ser = serial.Serial(get_port_arduino(), '9600')

    time.sleep(5)  # если мало "поспать", не работает

    # говорим ардуино, что будем слушать клавиатуру только при отправке ? в сериал.
        
    #ser.write(bytes('!', 'UTF-8'))

    # TODO: нужно сделать отправление в сериал символа, который даст знать ардуино, что питон-программа была отключена,
    # и можно продолжать выводить в ячейку брайля символы, введенные с клавиатуры
    try:
        while True:
            res = _app_menu(ser, apps)[1](ser)
    except BaseException as error:
            print("Отсутствует соединение с прибором")
            print(error)
            playSoundByFilename('audio/std_msg/ErrorConnection.wav')
            time.sleep(5)
    ser.close()
