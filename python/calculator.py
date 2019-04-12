import time
import serial
from audio import playSoundByFilename, pronounce
from serial_get_name import get_port_arduino
from listen_serial import listen_serial
from serial_hex import braille_to_char
from serial_hex import printLine

operations_dict = {
    "с": "+",
    "в": "-",
    "у": "*",
    "д": "/"
}


def startApp(ser):
    braille_text = ''
    joystick_ans = listen_serial(ser)
    while joystick_ans != 'l':
        if joystick_ans in 'udr':
            symbol = joystick_ans
        else:
            symbol = braille_to_char(joystick_ans)
        print(symbol)
        if symbol in '0123456789':
            braille_text += symbol
            printLine(symbol, ser)
        elif symbol == ',' and braille_text[-1] != ',':
            # Добавить запятую, если ещё не дрбавлена
            braille_text += symbol
            printLine(symbol, ser)
        elif symbol in 'свуд':
            if braille_text[-1] in '+-*/':
                # Изменить текущий оператор
                braille_text = braille_text[:-1] + operations_dict[symbol]
                printLine(symbol, ser)
                print(operations_dict[symbol])
            else:
                # Добавить оператор
                braille_text += operations_dict[symbol]
                printLine(symbol, ser)
                print(operations_dict[symbol])
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
                printLine(braille_text, ser)
                print('Результат: ' + braille_text)
            except (SyntaxError, ZeroDivisionError):
                print('Error')
                braille_text = ''
        joystick_ans = listen_serial(ser)


if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  # если мало "поспать", не работает
    res = startApp(ser)
    ser.close()