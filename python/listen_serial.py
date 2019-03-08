def listen_serial(ser):
    print('listen joystick or keyboard:')
    ser.flushInput()
    ser.write(bytes('?', 'UTF-8'))
    line = ser.readline()
    letter = str(line)[2]
    return letter if letter in 'lrduабвгдежзиклмнопрстуфхцчшщъыьэюя' else True
