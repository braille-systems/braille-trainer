from PyQt5.QtSerialPort import *


def get_port_arduino():
    for port in QSerialPortInfo.availablePorts():
        if port.productIdentifier() == 29987:
            return port.portName()
