#coding: utf8
import serial
_ser = 0
def serial_begin(port, baudrate):
   """
   serial_init(var port)
      port - port name
   Инициализация и открытие Serial
   """
   _ser = serial.Serial(port, baudrate, timeout = 5)
   if _ser.is_open == False:
      _ser.open()

def serial_write(letter):
   """
   serial_write(var letter)
   Печать буквы в Serial
   returns 1 - без ошибок
           0 - при ошибке
   
   Перед запуском begin_serial 
   """
   if _ser == 0:
      return 0
   _ser.write(ord(letter.lower())) #Пока так, но нужно исправить.
   res = _ser.read(1) #Ждет ответа 5 секунд
   if len(res) == 0 or res == b'0':
      return 0
   return 1

def serial_close():
   """
   serial_close():
   закрыть Serial
   """
   if _ser != 0 and _ser.is_open:
      _ser.close()
   _ser = 0