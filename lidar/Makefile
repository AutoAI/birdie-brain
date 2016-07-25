CC = g++ 
CFLAGS = -g -Wall -Werror

default: executable

executable: LidarPacket.o packetRead.o
	$(CC) $(CFLAGS) -o executable LidarPacket.o	packetRead.o

packetRead.o: packetRead.cpp
	$(CC) $(CFLAGS) -c packetRead.cpp

LidarPacket.o: LidarPacket.cpp
	$(CC) $(CFLAGS) -c LidarPacket.cpp

clean: 
	rm -rf *.o executable
