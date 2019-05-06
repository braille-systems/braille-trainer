"""
Немного изменённый serial-hex
Оказалось, в команде from serial-hex import (что-то)
питон видит зарезервированное слово hex и выдаёт ошибку
"""
import serial
import time
import threading
from serial_get_name import get_port_arduino
# from audio import pronounce
from listen_serial import listen_serial

def charToBraille(char):
    """
    Converts digit sign, digits or Russian letters to Braille string.
    Picture with braille symbols: github.com/zuevval/braille/doc/
    "char" is a digit sign, digit or Russian letter.

    """
    # print(char)

    is_letter = 0

    # is digit sign?
    if char == '#':
        data = '001111'
        return data

    if char == ' ':
        data = '000000'
        return data

    # is digit?
    if char in {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}:
        if char == '0':
            return '010110'
        if char == '1':
            return '100000'
        if char == '2':
            return '110000'
        if char == '3':
            return '100100'
        if char == '4':
            return '100110'
        if char == '5':
            return '100010'
        if char == '6':
            return '110100'
        if char == '7':
            return '110110'
        if char == '8':
            return '110010'
        if char == '9':
            return '010100'
        """
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
        """

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

    if char in {'-', ',', '.', '?', '!', ')', '(', ':'}:
        # dots 1
        data = '0'

        # dot 2
        if char in {'.', ',', '!', '?', ':', ')', '('}:
            data = data + '1'
        else:
            data = data + '0'

        # dot 3
        if char in {'!', '?', '-', ')', '('}:
            data = data + '1'
        else:
            data = data + '0'

        # dot 4
        data = data + '0'

        # dot 5
        if char in {'.', '!', ':', ')', '('}:
            data = data + '1'
        else:
            data = data + '0'

        # dot 6
        if char in {'.', '?', '-', ')', '('}:
            data = data + '1'
        else:
            data = data + '0'


    return data


def braille_to_char(data):
    print(data)
    """
    Converts Braille string to digit sign, digit or Russian letter.

    "data" is Braille string.

    """
    for letter in range(ord('а'), ord('я') + 1):
        if data == charToBraille(chr(letter)):
            return chr(letter)
    if data == '100001':
        return 'ё'
    for number in range(ord('0'), ord('9') + 1):
        if data == charToBraille(chr(number)):
            return chr(number)
    if data == '001111':
        return '#'
    if data == '000000':
        return ' '
    if data == '010011':
        return '.'
    if data == '010000':
        return ','
    if data == '011010':
        return '!'
    if data == '011001':
        return '?'
    if data == '010010':
        return ':'
    if data == '001001':
        return '-'
    if data == '011011':
        return ')'
    return ''


def printBraille (brArray, ser):
    """prints string in format: '000000', '010101', etc"""
    print(brArray)
    ser.write(bytes(brArray, 'UTF-8'))
    time.sleep(2)

    
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
            time.sleep(1.7)
        data = charToBraille(line[i])
        print(data)
        ser.write(bytes(data, 'UTF-8'))
        # pronounce(line[i])
        time.sleep(2)
        if len(line) < 2: #if line is not long so break unnecessary
            return
        ans = listen_serial(ser, requiresReturn=True)
        if ans in 'ldru':
            print('breaking printLine due to joystick signal:' + ans)
            return ans

def serTest():
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  # если мало "поспать", не работает
    printLine('ввод', ser)
    ser.close()

#print(braille_to_char('110000'))
#serTest()
