from PyQt5.QtSerialPort import *


def get_port_arduino():
    """
    Automatically detects the COM-port to which Braille trainer is connected.
    """
    for port in QSerialPortInfo.availablePorts():
        if port.productIdentifier() == 29987:
            return port.portName()
