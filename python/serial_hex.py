"""
Немного изменённый serial-hex
Оказалось, в команде from serial-hex import (что-то)
питон видит зарезервированное слово hex и выдаёт ошибку
"""
import serial
import time
from audio import pronounce
def charToBraille (char):
    print(char)
    #russian letters: first dot
    if char in {'а', 'б', 'г', 'д', 'е', 'ё', 'з',
                'й', 'к', 'л', 'м', 'н', 'о', 'п', 'у',
                'р', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ',
                'ю', 'я'}:
        data = '1'
    else:
        data = '0'
        
    #dot 2
    if char in {'б', 'в', 'г', 'ж', 'и', 'й',
                'л', 'п', 'р', 'с', 'т', 'ф',
                'х', 'ч', 'ъ', 'ы', 'ь', 'э',
                'ю', 'я'}:
        data = data + '1'
    else:
        data = data + '0'

    #dot 3
    if char in {'з', 'й', 'к', 'л', 'м', 'н',
                'о', 'п', 'р', 'с', 'т', 'у',
                'ч', 'щ', 'ъ', 'ы', 'ь'}:
        data = data + '1'
    else:
        data = data + '0'

    #dot 4
    if char in {'в', 'г', 'д', 'ж', 'и', 'й',
                'м', 'н', 'п', 'с', 'т', 'ф',
                'ц', 'ч', 'щ', 'ы', 'ь', 'э',
                'я'}:
        data = data + '1'
    else:
        data = data + '0'

    #dot 5
    if char in {'в', 'г', 'д', 'е', 'ж', 'з',
                'н', 'о', 'р', 'т', 'х', 'ч',
                'ш', 'ъ', 'ь', 'ю'}:
        data = data + '1'
    else:
        data = data + '0'
    
    #dot 6
    if char in {'в', 'ё', 'з', 'й', 'у', 'ш',
                'щ', 'ъ', 'ы', 'ь', 'э', 'ю',
                'я'}:
        data = data + '1'
    else:
        data = data + '0'
    return data

def printLine (line, ser):
    for i in range(len(line)):
        data = charToBraille(line[i])
        print(data)
        ser.write(bytes(data, 'UTF-8'))
        #pronounce(line[i])
        time.sleep(2)

def serTest ():
    ser = serial.Serial('COM9', '9600')
    time.sleep(5) # если мало "поспать", не работает
    printLine('абвгдеёжзийклмнопрстуфхцчшщъыьюя', ser)
    ser.close()
    
#serTest()
