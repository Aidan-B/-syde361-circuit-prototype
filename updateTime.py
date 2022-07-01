import serial.tools.list_ports
import time

for port in serial.tools.list_ports.comports():
    # Teensyduino Serial Device
    if (port.vid == 0x16c0 and port.pid == 0x0483):
        teensy = serial.Serial(port=port.device, baudrate=9600)
        current_time = f"T{round(time.time())}"
        print(current_time)
        raw_time = current_time.encode('raw_unicode_escape')
        teensy.write(raw_time)
