# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'letter.ui'
#
# Created by: PyQt5 UI code generator 5.11.3
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_LetterWidget(object):
    def setupUi(self, LetterWidget):
        LetterWidget.setObjectName("LetterWidget")
        LetterWidget.resize(650, 400)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(LetterWidget.sizePolicy().hasHeightForWidth())
        LetterWidget.setSizePolicy(sizePolicy)
        LetterWidget.setMinimumSize(QtCore.QSize(94, 16))
        palette = QtGui.QPalette()
        brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Active, QtGui.QPalette.Midlight, brush)
        brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Active, QtGui.QPalette.Base, brush)
        brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Active, QtGui.QPalette.Window, brush)
        brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Inactive, QtGui.QPalette.Midlight, brush)
        brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Inactive, QtGui.QPalette.Base, brush)
        brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Inactive, QtGui.QPalette.Window, brush)
        brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Disabled, QtGui.QPalette.Midlight, brush)
        brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Disabled, QtGui.QPalette.Base, brush)
        brush = QtGui.QBrush(QtGui.QColor(255, 255, 255))
        brush.setStyle(QtCore.Qt.SolidPattern)
        palette.setBrush(QtGui.QPalette.Disabled, QtGui.QPalette.Window, brush)
        LetterWidget.setPalette(palette)
        self.gridLayout = QtWidgets.QGridLayout(LetterWidget)
        self.gridLayout.setObjectName("gridLayout")
        self.letter = QtWidgets.QLabel(LetterWidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.letter.sizePolicy().hasHeightForWidth())
        self.letter.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setFamily("Arial Rounded MT Bold")
        font.setPointSize(200)
        font.setBold(False)
        font.setWeight(50)
        font.setStyleStrategy(QtGui.QFont.PreferAntialias)
        self.letter.setFont(font)
        self.letter.setFrameShape(QtWidgets.QFrame.Panel)
        self.letter.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.letter.setTextFormat(QtCore.Qt.PlainText)
        self.letter.setScaledContents(True)
        self.letter.setAlignment(QtCore.Qt.AlignCenter)
        self.letter.setIndent(2)
        self.letter.setTextInteractionFlags(QtCore.Qt.NoTextInteraction)
        self.letter.setObjectName("letter")
        self.gridLayout.addWidget(self.letter, 0, 0, 1, 1)
        self.braille = QtWidgets.QLabel(LetterWidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHeightForWidth(self.braille.sizePolicy().hasHeightForWidth())
        self.braille.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setFamily("Courier New")
        font.setPointSize(72)
        font.setBold(True)
        font.setWeight(75)
        self.braille.setFont(font)
        self.braille.setFrameShape(QtWidgets.QFrame.Panel)
        self.braille.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.braille.setTextFormat(QtCore.Qt.PlainText)
        self.braille.setScaledContents(True)
        self.braille.setAlignment(QtCore.Qt.AlignCenter)
        self.braille.setWordWrap(False)
        self.braille.setObjectName("braille")
        self.gridLayout.addWidget(self.braille, 0, 1, 1, 1)

        self.retranslateUi(LetterWidget)
        QtCore.QMetaObject.connectSlotsByName(LetterWidget)

    def retranslateUi(self, LetterWidget):
        _translate = QtCore.QCoreApplication.translate
        LetterWidget.setWindowTitle(_translate("LetterWidget", "Вывод буквы"))
        self.letter.setText(_translate("LetterWidget", "A"))
        self.braille.setText(_translate("LetterWidget", ".o\n"
".o \n"
".o"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    LetterWidget = QtWidgets.QWidget()
    ui = Ui_LetterWidget()
    ui.setupUi(LetterWidget)
    LetterWidget.show()
    sys.exit(app.exec_())

