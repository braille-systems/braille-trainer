from PyQt5.QtSerialPort import *
def getPortArduino():
    for port in QSerialPortInfo.availablePorts():
        if port.productIdentifier() == 29987:
            return port.portName()
