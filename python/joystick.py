def listen_joystick(ser):
    print("listen: ")
    while 1:
        line = ser.readline()
        return str(line)[2]