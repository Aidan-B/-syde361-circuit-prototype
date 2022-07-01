import serial.tools.list_ports
import time

for port in serial.tools.list_ports.comports():
    # Open serial port of Teensyduino Serial Device (USB ID 16C0:0483)
    if (port.vid == 0x16c0 and port.pid == 0x0483):
        teensy = serial.Serial(port=port.device, baudrate=9600, timeout=1)
        teensy.write('P'.encode('raw_unicode_escape'))

        # Wait for reply
        while (not teensy.inWaiting()):
            if (teensy.inWaiting()):
                break

        while (teensy.inWaiting()):
            eof = "EOF\r\n".encode(("raw_unicode_escape"))
            newline = "\r\n".encode(("raw_unicode_escape"))
            
            # Ignore empty lines
            line = teensy.readline()
            while (line == newline):
                line = teensy.readline()
            
            # Receive the file from the serial buffer and write it to a file
            name = line.removesuffix(newline).decode("utf-8")
            data = teensy.read_until(eof).removesuffix(eof).decode("utf-8")
            if (name):
                with open(f"data/{name}", 'w') as file:
                    file.write(data)
                    # file.close()

