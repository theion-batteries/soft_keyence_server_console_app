import socket


def send_message(sock):
    """Send a message to the server."""
    message = input("Enter a message to send (type 'quit' to exit): ")
    if message == "quit":
        return False
    sock.sendall(message.encode())
    #sock.setblocking(False)

    data = sock.recv(1024)
    print(F"data received {data.decode()}")

    return True


def main():
    # Create a socket object
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    # Connect to the server on localhost:6666
    server_address = ('localhost', 6666)
    sock.connect(server_address)

    # Send messages until the user types "quit"
    while True:
        if not send_message(sock):
            break
    # Close the socket
    sock.close()


if __name__ == "__main__":
    main()
