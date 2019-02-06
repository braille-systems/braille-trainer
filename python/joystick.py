def listen_joystick(ser):
    print("listen: ")
    while 1:
        line = ser.readline()
        print(line)
        letter = str(line)[2]
        return letter if letter in ['l', 'r', 'd', 'u'] else True
