def listen_joystick(ser):
    print("listen: ")
    while 1:
        line = ser.readline()
        print(str(line)[2])