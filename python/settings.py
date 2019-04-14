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
    while joystick_ans:
        if joystick_ans == 'l':
	    return
        elif joystick_ans == 'u':
            i += 1
	    #voice(i % 2)	
	elif joystick_ans == 'd'
	    i -= 1
	    #voice(i % 2)
	elif joystick_ans == 'r':
	    if i % 2 == 0: # audio speed setting
		#fread('settings.ini', audiospeed)
	        #voice(audiospeed)	    
		joystick_ans = listen_serial(ser)
		while joystick_ans != 'l':
		    if joystick_ans == 'u':
		        #audiospeed += ?		 
		    elif joystick_ans == 'd':
		        #audiospeed -= ?
		    #clamp(audiospeed)
 	            #voice(current audio speed)		
		    joystick_ans = listen_serial(ser)
		#fwrite('settings.ini', audiospeed)
	    else:
		#fread('settings.ini', autoskip)
	        #voice(current autoskip state (yes or no))
		joystick_ans = listen_serial(ser)
		while joystick_ans != 'l':
		    if joystick_ans == 'u' or joystick_ans == 'd':
			#autoskip = !autoskip	
		    #voice(current autoskip)		
		    joystick_ans = listen_serial(ser)
		#fwrite('settings.ini', autoskip)
        joystick_ans = listen_serial(ser)


if __name__ == "__main__":
    ser = serial.Serial(get_port_arduino(), '9600')
    time.sleep(5)  # если мало "поспать", не работает
    res = startApp(ser)
    ser.close()