# Created on Sat April 4 2015

from kovan import *
import socket

HOST_FOR_SERVER = ''  # Symbolic name meaning all available interfaces
HOST_FOR_CLIENT = 'localhost'
PORT = 5107  # Arbitrary non-privileged port

print "I am the Client!"

def main():
    """ Calls the   TEST   functions in this module. """
    client_or_server = input('Enter C (for Client) or S (for Server)')
    if client_or_server.lower() == "s":
        server()
    else:
        client()


def server():
    """
    Prints what it hears from the client.
    Will run on the Link and execute the commands sent it.
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((HOST_FOR_SERVER, PORT))
    sock.listen(1)  # Listen for exactly one connection
    conn, addr = sock.accept()
    print('Connected by', addr)

    while True:
        data = conn.recv(1024)
        if not data:
            break
        print('Received from laptop:', repr(data))
    conn.close()


def client():
    """ Send words to echo. """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST_FOR_CLIENT, PORT))
    while True:
        s = input("Enter string to send: ")
        if s == "":
            break
        sock.sendall(bytes(s, 'utf-8'))
    sock.close()

client()
