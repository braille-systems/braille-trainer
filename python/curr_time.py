from datetime import datetime
import time
import serial


def curr_time():
    dt = datetime.now()
    hour = dt.hour
    minute = dt.minute
    hm = str(hour) + ' ' + str(minute)
    # print(hm)
    # ser.write(bytes(hm, 'UTF-8'))
    return hm


def test_time():
    ser = serial.Serial('COM7', '9600')
    time.sleep(5)  # если мало "поспать", не работает
    curr_time(ser)
    ser.close()


# test_time()
