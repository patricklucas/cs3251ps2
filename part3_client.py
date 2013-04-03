#!/usr/bin/env python

import socket
import sys

def part1_client(addr, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((addr, port))

    while True:
        chunk = sys.stdin.read(4096)

        if not chunk:
            break

        sock.send(chunk)

    sock.close()

if __name__ == '__main__':
    args = sys.argv[1:]

    if len(args) >= 2:
        addr = args[0]
        port = int(args[1])
    elif len(args) == 1:
        addr = "0.0.0.0"
        port = int(args[0])
    else:
        addr = "0.0.0.0"
        port = 1234

    part1_client(addr, port)
