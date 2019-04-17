import time
import serial
from audio import playSoundByFilename, pronounce
from serial_get_name import get_port_arduino
from listen_serial import listen_serial
from serial_hex import braille_to_char
from serial_hex import printLine

def startApp(ser):
    braille_text = ''
    i = 0
    joystick_ans = listen_serial(ser)
    
    while joystick_ans != 'l':
        if joystick_ans == 'u':
            i = i + 1
	    #voice(i % 2)	
        elif joystick_ans == 'd':
            i = i - 1
            #voice(i % 2)
        elif joystick_ans == 'r':
            if i % 2 == 0: # audio speed setting
                f = open('settings.ini', 'r')
                audiospeed = int(f.read(1))
                f.read(1)
                autoskip = int(f.read(1))
                f.close()
	        #voice(audiospeed)	    
                joystick_ans = listen_serial(ser)
                while joystick_ans != 'l':
                    if joystick_ans == 'u':
                        audiospeed += 1		 
                    elif joystick_ans == 'd':
                        audiospeed -= 1
                    if audiospeed > 9:
                        audiospeed = 9
                    elif audiospeed < 0:
                        audiospeed = 0
 	            #voice(current audio speed)		
                    joystick_ans = listen_serial(ser)
                f = open('settings.ini', 'w')
                f.write(str(audiospeed) + ' ' + str(autoskip))
                f.close()
            else:
                f = open('settings.ini', 'r')
                audiospeed = int(f.read(1))
                f.read(1)
                autoskip = int(f.read(1))
                f.close()
	        #voice(current autoskip state (yes or no))
                joystick_ans = listen_serial(ser)
                while joystick_ans != 'l':
                    if joystick_ans == 'u' or joystick_ans == 'd':
                        autoskip = 1 - autoskip	
		    #voice(current autoskip)		
                    joystick_ans = listen_serial(ser)
                f = open('settings.ini', 'w')
                f.write(str(audiospeed) + ' ' + str(autoskip))
                f.close()
        joystick_ans = listen_serial(ser)

if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  
    res = startApp(ser)
    ser.close()