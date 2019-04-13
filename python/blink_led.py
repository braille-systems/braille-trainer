#!/usr/bin/env python
"""Basic blinking led example.

blinks a LED connected to GPIO PG11
"""

import os
import sys

if not os.getegid() == 0:
    sys.exit('Script must be run as root')


from time import sleep
from pyA20.gpio import gpio
from pyA20.gpio import port

__author__ = "Stefan Mavrodiev"
__copyright__ = "Copyright 2014, Olimex LTD"
__credits__ = ["Stefan Mavrodiev"]
__license__ = "GPL"
__version__ = "2.0"
__maintainer__ = __author__
__email__ = "support@olimex.com"

#PG11 <=> IOG11, right side if usb faces to us
#PG6 <=> TX1, left side
#PG7 <=> RX1, left side under TX1
#PA15 <=> MO (MOSI), left side under RX1
#PA16 <=> MI (MISO)
#PA14 <=> CLK
#PA13 <=> CS
led = port.PA13


gpio.init()
gpio.setcfg(led, gpio.OUTPUT)

try:
    print ("Press CTRL+C to exit")
    while True:
        gpio.output(led, 1)
        sleep(0.1)
        gpio.output(led, 0)
        sleep(0.1)

        gpio.output(led, 1)
        sleep(0.1)
        gpio.output(led, 0)
        sleep(0.1)

        sleep(0.6)

except KeyboardInterrupt:
    print ("Goodbye.")
