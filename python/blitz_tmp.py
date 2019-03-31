import serial
import random
from audio import pronounce
from audio import playSoundByFilename
from serial_hex import printLine
from listen_serial import listen_serial


def blitzgame(ser, indexes_of_audio):   
    modes_of_blitz = []                                         #массив функций режимов игры
    num_of_modes = len(modes_of_blitz)

    playSoundByFilename(indexes_of_audio[0])                    #произносит описания блица, просит дёрнуть стик вправо, нужен ли тут принт
    joystick_ans = listen_serial(ser)
    while joystick_ans:
        if joystick_ans == 'r':                                 #переходим к выбору режима блица
            i = 0
            while joystick_ans:                                 #сдвиг стика влево, кажется интуитивным способом выхода из приложения
                playSoundByFilename(indexes_of_audio[i + 1])    #произносит описание режима чтение
                if joystick_ans == 'd':
                    i += 1
                    i %= num_of_modes
                    playSoundByFilename(indexes_of_audio[i + 1])
                if joystick_ans == 'u':
                    i -= 1
                    i %= num_of_modes
                    playSoundByFilename(indexes_of_audio[i + 1])
                if joystick_ans == 'r':
                    modes_of_blitz[i]()                         #тут вызывавет функцию из массива режимов
                if joystick_ans == 'l':
                    return


def reading_mode(ser):                                          #режим распознавания выведенных букв
    ALF = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя'                   #раз уж это блитц-опрос, то последовательность букв в вопросах должна быть каждый раз разной (предлагаю отказаться от идеи пулла)
    wrong_num = 0
    correct_num = 0
    
    while mistake_counter < 3
        i = random.randint(0, 32)
        printLine(ALF[i], ser)                                  #вывод буквы на ячейку

        ans = </РАСПОЗНАВАНИЕ ГОЛОСОВГО ОТВЕТА?>
        if ans == ALF[i]:                                       #счёт очков
            correct_num += 1
        else
            wrong_num += 1

    playSoundByFilename(</АУДИО С РЕЗУЛЬТАТАМИ>)


def writing_mode(ser):                                          #режим самостоятельного ввода озвученных букв
    ALF = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя'    
    wrong_num = 0
    correct_num = 0
        
    while mistake_counter < 3
        i = random.randint(0, 32)
        pronounce(ALF[i])                                       #озвучивание буквы
        
        ans = </ВВОД ОЗВУЧЕННОЙ ВЫШЕ БУКВЫ>
        if ans == ALF[i]:
            correct_num += 1
        else
            wrong_num += 1

    playSoundByFilename(</АУДИО С РЕЗУЛЬТАТАМИ>)
