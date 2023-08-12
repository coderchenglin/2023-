cc=g++

.PHONY:all
all:udpClient udpServer


udpClient:udpClient.cc
	$(cc) -o $@ $^ -lpthread -std=c++11
udpServer:udpServer.cc
	$(cc) -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f udpClient udpServer
