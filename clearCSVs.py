import serial.tools.list_ports

for port in serial.tools.list_ports.comports():
    # Teensyduino Serial Device
    if (port.vid == 0x16c0 and port.pid == 0x0483):
        teensy = serial.Serial(port=port.device, baudrate=9600)
        teensy.write("C".encode('raw_unicode_escape'))
