# Created on Sat April 4 2015

from kovan import *
import socket
import sys
		
PORT_TO_SHARE = 2105  # Server and client must use the same port
SERVER_IP = 'localhost'  # '192.168.1.129'

print "I am the Server, running on the Link."

class Connection():
    def __init__(self, sock):
        self.sock = sock

    def get(self, message_length=1):
        chunks = []
        bytes_received = 0
        while True:
            if bytes_received >= message_length:
                break
            chunk = self.sock.recv(min(message_length - bytes_received,
                                       2048))
            if chunk == b'':
                # TODO: Make this message more clear
                raise RuntimeError('socket connection broken')
            chunks.append(chunk)
            bytes_received += len(chunk)

        print(chunks)
        s = ""
        for chunk in chunks:
            s += chunk.decode('utf-8')

        return s

    def send(self, s):
        self.sock.sendall(bytes(s, 'utf-8'))

    def close(self, shutdown=None):
        if shutdown:
            self.sock.shutdown(shutdown)
        self.sock.close()

class Server(Connection):
    def __init__(self, port):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.bind(("", port))
        sock.listen(1)
        connection, address = sock.accept()
        Connection.__init__(self, connection)

        print("Connected to address:" + repr(address))
        # TODO: Error handling.

def main():
	global PORT_TO_SHARE
	
	c = Server(PORT_TO_SHARE)
	# Imagine Botball commands like   motor   here ...
	listen(c)
	
	# Imagine Botball commands like   motor   here ...
	listen(c)
	
	c.close(socket.SHUT_RDWR)

def listen(c):
    print("Listening ...")

    while True:
        s = c.get(1)
        if s.lower() == "q":
            break
        print('Received: ' + s)
        sys.stdout.flush()

main()
