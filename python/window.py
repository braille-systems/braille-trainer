#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys
from serial_hex import charToBraille
import PyQt5
from PyQt5.QtWidgets import *
from threading import Thread


class WindowBraille(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
    
    def initUI(self):
        self.setGeometry(50, 100, 1000, 200)
        self.setWindowTitle('Буква на языке Брайля')
        layout = QGridLayout()
        layout.setColumnStretch(1, 4)
        self.letterLabel = QLabel('A')
        self.letterLabel.setFont(PyQt5.QtGui.QFont("Arial", 500, PyQt5.QtGui.QFont.Bold))
        layout.addWidget(self.letterLabel, 0, 0)
        self.brailleLabel = QLabel('. .\n. .\n. .')
        self.brailleLabel.setFont(PyQt5.QtGui.QFont("Arial", 100, PyQt5.QtGui.QFont.Bold))
        layout.addWidget(self.brailleLabel, 0, 2)
        self.setLayout(layout)
        self.show()
    
    def graphic_show(self, letter):
        data = charToBraille(letter).replace('0', ' ').replace('1', '.')
        data = data[0:2] + '\n' + data[2:4] + '\n' + data[4:6]
        print(data)
        self.brailleLabel.setText(data)
        self.letterLabel.setText(letter)
    
    def open(self):
        self.show()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = WindowBraille()
    thread1 = Thread(target=app.exec_)
    thread1.start()
    ex.graphic_show('б')
