import serial_hex
from PyQt5 import (QtCore, QtGui, QtWidgets)
from ui_letter import Ui_LetterWidget
class LetterWidget(QtWidgets.QWidget, Ui_LetterWidget):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
    def setLetter(self,letter):
        self.letter.setText(letter.upper())
        data = serial_hex.charToBraille(letter).replace('0','.').replace('1','O')
        data = data[0:2]+'\n'+data[2:4]+'\n'+data[4:6]
        self.braille.setText(data)

