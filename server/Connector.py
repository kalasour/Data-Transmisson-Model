import serial
ser = serial.Serial()
ser.port = 'COM4'
ser.baudrate = 9600
ser.open()
cmd=''
ser.write(cmd.encode('ascii'))
while True:
    out = ser.readline()
    if(out==b'Input:\n'):
        cmd = input("Enter command or 'exit':")+ '\r\n'
        ser.write(cmd.encode('ascii'))
    if cmd == 'exit'+ '\r\n':
        ser.close()
        exit()
    else:
        print(out.decode("utf-8")+str(ser.inWaiting()))
        