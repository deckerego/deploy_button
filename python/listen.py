#!/usr/bin/python

import sys, time, getopt, subprocess
import usb.core, usb.util
import logging
import inspect

logging.basicConfig()
logger = logging.getLogger()
logger.setLevel(10)

def state_changed(value):
    if value > 0:
        logger.debug("Deployed!")
        #subprocess.check_call(["open", "/System/Library/Frameworks/ScreenSaver.framework/Versions/A/Resources/ScreenSaverEngine.app"])
        subprocess.check_call(["open", "/Applications/Google Chrome.app", "http://member.angieslist.com/"])
    else:
        logger.debug("Done!")

class Sensor:
    trinket = False
    endpoint = 0x81

    def __init__(self):
        self.reconnect()

    def __del__(self):
        self.trinket = False

    def reconnect(self):
        self.trinket = self.__findTrinket()

        if self.trinket != False:
            self.endpoint = self.trinket[0][(0,0)][0]
            logger.info("Button Ready");

    def readline(self):
        if not self.trinket:
            logging.error('No trinket connected, trying again...')
            self.reconnect()
            return self.readline()

        try:
            char_buffer = ''
            while True:
                data = self.trinket.read(self.endpoint.bEndpointAddress, self.endpoint.wMaxPacketSize)
                readCnt = len(data)
                if readCnt > 0:
                    char_buffer += bytearray(data)
                    if '\r\n' in char_buffer[-2:] and len(char_buffer.strip()) > 0:
                        return char_buffer.strip()

        except Exception as ex:
            exStr = str(ex).lower()
            if 'timeout' not in exStr:
                logging.error('USB read error', ex)
                self.trinket = False

    def __findTrinket(self):
        device = usb.core.find(idVendor = 0x1781, idProduct = 0x1111)
        if device == None or device == False or device == 0 :
            return False

        device.set_configuration()
        return device

sensor = Sensor()

old_value = 0
while True:
    new_value = int(sensor.readline())
    if new_value != old_value:
        state_changed(new_value)
    old_value = new_value
    time.sleep(0.1)
