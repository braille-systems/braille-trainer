"""
Немного изменённый serial-hex
Оказалось, в команде from serial-hex import (что-то)
питон видит зарезервированное слово hex и выдаёт ошибку
"""
import serial
import time
from serial_get_name import get_port_arduino
# from audio import pronounce


def charToBraille(char):
    """
    Converts digit sign, digits or Russian letters to Braille string.

    "char" is a digit sign, digit or Russian letter.

    """
    print(char)

    is_letter = 0

    # is digit sign?
    if char == '#':
        data = '001111'
        return data

    # is digit?
    if char in {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}:
        # dot 1
        data = '0'

        # dot 2
        if char in {'1', '2', '3', '4', '5', '6', '7', '8'}:
            data = data + '1'
        else:
            data = data + '0'

        # dot 3
        if char in {'2', '6', '7', '8', '9', '0'}:
            data = data + '1'
        else:
            data = data + '0'

        # dot 4
        data = data + '0'

        # dot 5
        if char in {'0', '3', '4', '6', '7', '9'}:
            data = data + '1'
        else:
            data = data + '0'

        # dot 6
        if char in {'0', '4', '5', '7', '8'}:
            data = data + '1'
        else:
            data = data + '0'

    else:
        # dot 1
        if char in {'а', 'б', 'г', 'д', 'е', 'ё', 'з',
                    'й', 'к', 'л', 'м', 'н', 'о', 'п', 'у',
                    'р', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ',
                    'ю', 'я'}:
            data = '1'
        else:
            data = '0'

        # dot 2
        if char in {'б', 'в', 'г', 'ж', 'и', 'й',
                    'л', 'п', 'р', 'с', 'т', 'ф',
                    'х', 'ч', 'ъ', 'ы', 'ь', 'э',
                    'ю', 'я'}:
            data = data + '1'
        else:
            data = data + '0'

        # dot 3
        if char in {'з', 'й', 'к', 'л', 'м', 'н',
                    'о', 'п', 'р', 'с', 'т', 'у',
                    'ч', 'щ', 'ъ', 'ы', 'ь'}:
            data = data + '1'
        else:
            data = data + '0'

        # dot 4
        if char in {'в', 'г', 'д', 'ж', 'и', 'й',
                    'м', 'н', 'п', 'с', 'т', 'ф',
                    'ц', 'ч', 'щ', 'ы', 'ь', 'э',
                    'я'}:
            data = data + '1'
        else:
            data = data + '0'

        # dot 5
        if char in {'в', 'г', 'д', 'е', 'ж', 'з',
                    'н', 'о', 'р', 'т', 'х', 'ч',
                    'ш', 'ъ', 'ь', 'ю'}:
            data = data + '1'
        else:
            data = data + '0'

        # dot 6
        if char in {'в', 'ё', 'з', 'й', 'у', 'ш',
                    'щ', 'ъ', 'ы', 'ь', 'э', 'ю',
                    'я'}:
            data = data + '1'
        else:
            data = data + '0'

    return data


def printLine(line, ser):
    """
    Display string on Braille trainer.

    "line" is a string to display.

    "ser" is an open Serial connection with Braille trainer
    (with Arduino board having '../arduino/printText/printText.ino' sketch loaded).

    """
    for i in range(len(line)):
        if i > 0 and line[i] == line[i - 1]:
            ser.write(bytes('000000', 'UTF-8'))
            time.sleep(2)
        data = charToBraille(line[i])
        print(data)
        ser.write(bytes(data, 'UTF-8'))
        # pronounce(line[i])
        time.sleep(2)


def serTest():
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  # если мало "поспать", не работает
    printLine('ввод', ser)
    ser.close()

#serTest()
