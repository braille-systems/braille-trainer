import sys
import serial
from letter import LetterWidget
from PyQt5.QtWidgets import QApplication
from PyQt5.QtCore import QThread


class UnitProcessor(QThread):

    def __init__(self, lu):
        QThread.__init__(self)
        self.lu = lu

    def __del__(self):
        self.wait()

    def run(self):
        self.lu.setLetter('а')
        self.sleep(2)
        self.lu.setLetter('б')
        self.sleep(2)
        self.lu.setLetter('в')
        self.sleep(2)
        print('work')

if __name__ == "__main__":        
    app = QApplication(sys.argv)
    lu = LetterWidget()
    lu.setLetter('')
    lu.show()
    thread1 = UnitProcessor(lu)
    thread1.start()
    sys.exit(app.exec_())
