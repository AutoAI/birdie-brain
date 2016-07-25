#include "LidarPacket.hpp"

LidarPacket::LidarPacket(char* bytes) {
	for (int i = 0; i<42; i++) { //header is the first 42 bytes
		header[i] = bytes[i];
	}

	for (int i = 0; i<12; i++) {
		dataBlockPopulate(i, bytes);
	}
	//timestamp
	timestamp = ((unsigned int)(bytes[1242]) << 24) | ((unsigned int)(bytes[1243]) << 16) | ((unsigned int)(bytes[1244]) << 8) | bytes[1245];

	//factory
	factory = ((unsigned short)(bytes[1246]) << 8) | (bytes[1247]);


}

void LidarPacket::dataBlockPopulate(int i, char* bytes) {
	dataBlocks[i].flag = shortFromBytes(bytes[42+100*i], bytes[43+100*i]);
	dataBlocks[i].azimuth = shortFromBytes(bytes[44+100*i], bytes[45+100*i]);
	for (int j = 0; j<32; j++) {
		channelDataPopulate(i, j, bytes);
	}

}

void LidarPacket::channelDataPopulate(int i, int j, char* bytes) {
	dataBlocks[i].chanelDataArraySomeoneShouldNameThis[j].distance = shortFromBytes(bytes[46+(100*i)+(3*j)], bytes[47+(100*i)+(3*j)]);
	dataBlocks[i].chanelDataArraySomeoneShouldNameThis[j].reflectivity = bytes[48+(100*i)+(3*j)];
}
unsigned short LidarPacket::shortFromBytes(byte a, byte b) {
   return ((unsigned short)a << 8) | b;
}
