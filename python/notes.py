import time
import serial
from audio import playSoundByFilename
from serial_get_name import get_port_arduino
from listen_serial import listen_serial


class Note(object):
    def __init__(self, title, body):
        self.title = title
        self.body = body

    def __str__(self):
        return self.title

    def __repr__(self):
        return self.__str__()

    def new_note(title, body):
        with open('saved_notes.txt', "a", encoding = "utf-8") as file:
            file.write("\n" + title + " " + body)
            return Note(title, body)

    def delete_note(title, body):
        with open('saved_notes.txt', encoding = "utf-8") as file:
            for line in file:
                print(line.split())
                temp = line.split()

def startApp(ser):
    notes = ["New note"]
    with open('saved_notes.txt', encoding='utf-8') as file:
        for line in file:
            if line != "" and line != "\n":
                temp = line.split()
                notes.append(Note(temp[0], temp[1]))


    # joystick_ans = (str(input())+' ')[0] #technical substitution for testing
    i = 0
    joystick_ans = listen_serial(ser)
    while joystick_ans != 'l':
        print(joystick_ans)

        if joystick_ans == 'd':
            if i == len(notes) - 1:
                i = 0
            else:
                i = i + 1
            if notes[i] == "New note":
                playSoundByFilename('')
            else: playSoundByFilename('')

        if joystick_ans == 'u':
            if i == 0:
                i = len(notes) - 1
            else:
                i = i - 1
            if notes[i] == "New note":
                playSoundByFilename('')
            else: playSoundByFilename('')

        joystick_ans = listen_serial(ser)
        # joystick_ans = (str(input())+' ')[0]
    pass


if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  # если мало "поспать", не работает
    res = startApp(ser)
    ser.close()
