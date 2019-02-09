import main
import notes
import alphabet
# import clocks
import serial
from audio import playSoundByFilename

from joystick import listen_joystick
import time
from serial_get_name import get_port_arduino


def _app_menu(ser, apps):
    """apps menu"""
    i = 0
    app = apps[0]
    playSoundByFilename(app[0])
    print(app[0])
    joystick_ans = listen_joystick(ser)
    print(joystick_ans, i)
    while joystick_ans:
        print(joystick_ans)
        if joystick_ans == 'd':
            if i == len(apps) - 1:
                i = 0
            else:
                i = i + 1
            app = apps[i]
            playSoundByFilename(app[0])
            print(i)
        if joystick_ans == 'u':
            if i == 0:
                i = len(apps) - 1
            else:
                i = i - 1
            app = apps[i]
            playSoundByFilename(app[0])
            print(i)
        joystick_ans = listen_joystick(ser)
        if joystick_ans == 'r':
            break
    return app


if __name__ == "__main__":
    apps = [
        ['audio/apps/eduApp.wav', main.startApp],
        ['audio/apps/notesApp.wav', notes.startApp],
        ['audio/apps/alphabetApp.wav', aphabet.startApp],
        ['audio/apps/clocksApp.wav', main.startApp]
    ]
    i = 0
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  # если мало "поспать", не работает
    while True:
        res = _app_menu(ser, apps)[1](ser)
    # ser.close()
