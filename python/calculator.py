import time
import serial
from audio import playSoundByFilename, pronounce
from serial_get_name import get_port_arduino
from listen_serial import listen_serial
from serial_hex import braille_to_char
from serial_hex import printLine
from speech_synthesizer import text_to_speech

operations_dict = {
    "с": ["+", "плюс", "r"],
    "в": ["-", "минус", "l"],
    "у": ["*", "умножить на", "u"],
    "д": ["/", "делить на", "d"],
}

def startApp(ser):
    braille_text = ''
    joystick_ans = listen_serial(ser, "calculator")
    print(joystick_ans)
    while joystick_ans != 'l':

        if joystick_ans == '000000':
            oper_joy_listen = listen_serial(ser)
            if oper_joy_listen in 'udrl':
                for oper in operations_dict:
                    if operations_dict[oper][2] == oper_joy_listen:
                        text_to_speech(operations_dict[oper][1])
                        braille_text = braille_text + operations_dict[oper][0]
                        printLine(oper, ser)
                        print(operations_dict[oper][0])

        if joystick_ans in 'udr':
            symbol = joystick_ans
        else:
            symbol = braille_to_char(joystick_ans)
        print(symbol)
        if symbol in '0123456789':
            text_to_speech(symbol)
            braille_text += symbol
            printLine(symbol, ser)
        elif symbol == ',' and braille_text[-1] != ',':
            # Добавить запятую, если ещё не доавлена
            braille_text += symbol
            printLine(symbol, ser)
        elif symbol in 'свуд':
            if braille_text[-1] in '+-*/':
                # Изменить текущий оператор
                text_to_speech(operations_dict[symbol][1])
                braille_text = braille_text[:-1] + operations_dict[symbol][0]
                printLine(symbol, ser)
                print(operations_dict[symbol][0])
            else:
                # Добавить оператор
                braille_text += operations_dict[symbol][0]
                printLine(symbol, ser)
                print(operations_dict[symbol][0])
        elif symbol == 'u':
            # Очистить
            braille_text = ''
        elif symbol == 'd':
            # Удалить последний символ
            braille_text = braille_text[:-1]
            if len(braille_text) != 0:
                printLine(braille_text[len(braille_text) - 1], ser)
        elif symbol == 'r':
            # Найти результат вычисления
            try:
                expression = braille_text + "="
                braille_text = str(eval(braille_text))
                text_to_speech("равно" + braille_text)
                printLine(braille_text, ser)
                print('Результат: ' + braille_text)
            except (SyntaxError, ZeroDivisionError):
                print('Error')
                braille_text = ''
        joystick_ans = listen_serial(ser, "calculator")


if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  # если мало "поспать", не работает
    res = startApp(ser)
    ser.close()
