import serial
import random
import configparser as cfgps
import os
import time
from serial_hex import printLine
from listen import listen_symbol
from listen_serial import listen_serial
from serial_get_name import get_port_arduino
from speech_synthesizer import text_to_speech


def startApp(ser):
    path = "blitz.ini"
    num_of_modes = 2
    if not os.path.exists(path):                                # тут проверяем на существование файла с максимальным счётом
        config = cfgps.ConfigParser()
        config.add_section("Highscores")
        config.set("Highscores", "writing", "0")
        config.set("Highscores", "reading", "0")
        with open(path, "w") as config_file:
            config.write(config_file)
    modes_of_blitz = [reading_mode, writing_mode]                                         # массив функций режимов игры
    #text_to_speech("для перехода в меню выбора режима дёрните джойстик вправо")           # произносит описания блица, просит дёрнуть стик вправо, нужен ли тут принт
    #print("для перехода в меню выбора режима дёрните джойстик вправо")
    #joystick_ans = listen_serial(ser)
    lines_for_modes = ["Режим чтения", "Режим ввода с помощью клавиатуры"]
    joystick_ans = 'r'
    while joystick_ans:
        if joystick_ans == 'r':                                 # переходим к выбору режима блица
            i = 0
            text_to_speech(lines_for_modes[i])
            print(lines_for_modes[i])
            while joystick_ans:                                 # сдвиг стика влево, кажется интуитивным способом выхода из приложения
                joystick_ans = listen_serial(ser, "blitzModes")
                if joystick_ans == 'd':
                    i += 1
                    i %= num_of_modes
                    text_to_speech(lines_for_modes[i])
                    print(lines_for_modes[i])
                elif joystick_ans == 'u':
                    i -= 1
                    i %= num_of_modes
                    text_to_speech(lines_for_modes[i])
                    print(lines_for_modes[i])
                elif joystick_ans == 'r':
                    modes_of_blitz[i](ser, path)  # тут вызывавет функцию из массива режимов
                    text_to_speech("Вы вернулись в меню выбора режима блиц-опроса")
                    print("Вы вернулись в меню выбора режима блиц-опроса")
                elif joystick_ans == 'l':
                    return
        elif joystick_ans == 'l':
            return
        joystick_ans = listen_serial(ser, "blitzModes")


def reading_mode(ser, path):                                          # режим распознавания выведенных букв
    ALF = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя'                   # раз уж это блитц-опрос, то последовательность букв в вопросах должна быть каждый раз разной (предлагаю отказаться от идеи пулла)
    wrong_num = 0
    correct_num = 0
    
    while wrong_num < 3:
        i = random.randint(0, 32)
        printLine(ALF[i], ser)                                  # вывод буквы на ячейку

        ans = listen_symbol()
        if ans == ALF[i]:                                       # счёт очков
            correct_num += 1
            text_to_speech("верно")
        else:
            wrong_num += 1
            text_to_speech("неверно")
    [upd_flag, hs] = update_hs(path, correct_num, "reading")
    if upd_flag:
        text_to_speech("поздравляю, вы установили новый рекорд")
    else:
        result_line = "Вы набрали " + str(correct_num) + " очков"
        text_to_speech(result_line)
    final_line = "Текущий максимальный счёт " + str(hs) + " очков"
    text_to_speech(final_line)
    return


def writing_mode(ser, path):               # режим самостоятельного ввода озвученных букв
    ALF = 'абвгдеёжзийклмнопрстуфхцчшщъыьэюя'    
    wrong_num = 0
    correct_num = 0
        
    while wrong_num < 3:
        i = random.randint(0, 32)
        text_to_speech(ALF[i])                                       #озвучивание буквы
        
        ans = listen_serial(ser)
        if ans == ALF[i]:                                       # счёт очков
            correct_num += 1
            text_to_speech("верно")
        else:
            wrong_num += 1
            text_to_speech("неверно")
    [upd_flag, hs] = update_hs(path, correct_num, "writing")
    if upd_flag:
        text_to_speech("поздравляю, вы установили новый рекорд")
    else:
        result_line = "Вы набрали " + str(correct_num) + " очков"
        text_to_speech(result_line)
    final_line = "Текущий максимальный счёт " + str(hs) + " очков"
    text_to_speech(final_line)
    return


def update_hs(path, new_result, mode):
    config = cfgps.ConfigParser()
    config.read(path)
    upd_flag = False
    old_result = int(config.get("Highscores", mode))
    if new_result > old_result:
        config.set("Highscores", mode, str(new_result))
        with open(path, "w") as config_file:
            config.write(config_file)
        upd_flag = True
        old_result = new_result
    return [upd_flag, old_result]


if __name__ == "__main__":
    #ser = serial.Serial(get_port_arduino(), '9600')
    #time.sleep(5)  # если мало "поспать", не работает
    ser = 1

    def listen_serial(ser):
        return input()

    def printLine(stri, ser):
        return print(stri)

    def listen_symbol():
        return input()

    def text_to_speech(stri):
        return print(stri)

    startApp(ser)
    #ser.close()
