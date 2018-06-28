import socket

if (__name__ == "__main__"):

	HOST, PORT = "localhost", 8080
	s = socket.socket()
	try:
		s.connect((HOST, PORT))
		s.send(b"hello world")
		print("Response: " + s.recv(1024).decode())
	except:
		print("Could not connect!")