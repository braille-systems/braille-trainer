import serial_hex
from PyQt5 import (QtCore, QtGui, QtWidgets)
from ui_letter import Ui_LetterWidget


class LetterWidget(QtWidgets.QWidget, Ui_LetterWidget):
    def __init__(self):
        super().__init__()
        self.setupUi(self)

    def setLetter(self, letter):
        """
        Returns a letter to the PyQt5 screen.
        """

        self.letter.setText(letter.upper())
        data = serial_hex.charToBraille(letter).replace('0', '.').replace('1', 'O')
        data = data[0] + data[5] + '\n' + data[1] + data[4] + '\n' + data[2] + data[3]
        self.braille.setText(data)
