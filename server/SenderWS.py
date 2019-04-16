from simple_websocket_server import WebSocketServer, WebSocket
import serial.tools.list_ports
import serial
import io
comlist = serial.tools.list_ports.comports()
connected = []
ser = serial.Serial(timeout=1)
ser.port = 'COM4'
ser.baudrate = 9600
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

class SimpleEcho(WebSocket):
    def handle(self):
        text=self.data+'\r\n'
        ser.write(text.encode('ascii'))
        for line in sio:
            self.send_message(line)
    def connected(self):
        ser.open()
        sio.flush()
        print(self.address, 'connected')
            

    def handle_close(self):
        ser.close()
        print(self.address, 'closed')

for element in comlist:
    connected.append(element.device)
if(len(connected)>1):
    print("Connected COM ports: " + str(connected))
    ser.port = input("Please select COM port for Sender: ")
server = WebSocketServer('', 8888, SimpleEcho)
server.serve_forever()
