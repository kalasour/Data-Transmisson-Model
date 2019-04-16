from simple_websocket_server import WebSocketServer, WebSocket
import serial.tools.list_ports
import serial
import io
comlist = serial.tools.list_ports.comports()
connected = []
ser = serial.Serial(timeout=1)
ser.port = 'COM3'
ser.baudrate = 9600
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

class SimpleEcho(WebSocket):
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
    ser.port = input("Please select COM port for Receiver: ")
server = WebSocketServer('', 8989, SimpleEcho)
server.handle_request()
