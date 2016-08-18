#include "LidarPacket.hpp"
#include "point3d.hpp"
#include <math.h>
#include <cstdlib>

const float RADIANCONVERT = (3.141592653589 / 180);

LidarPacket::LidarPacket(char* bytes) {
	laserTable = (float*) malloc(16 * (sizeof(float)));
	laserTable[0] = -15;
	laserTable[1] = 1;
	laserTable[2] = -13;
	laserTable[3] = -3;
	laserTable[4] = -11;
	laserTable[5] = 5;
	laserTable[6] = -9;
	laserTable[7] = 7;
	laserTable[8] = -7;
	laserTable[9] = 9;
	laserTable[10] = -5;
	laserTable[11] = 11;
	laserTable[12] = -3;
	laserTable[13] = 13;
	laserTable[14] = -1;
	laserTable[15] = 15;

	for (int i = 0; i < 12; i++) {
		dataBlockPopulate(i, bytes);
	}
	//timestamp
	timestamp = ((unsigned int)(bytes[1203]) << 24) | ((unsigned int)(bytes[1202]) << 16) | ((unsigned int)(bytes[1201]) << 8) | bytes[1200];

	//factory
	factory = shortFromBytes(bytes[1204], bytes[1205]);

}

void LidarPacket::dataBlockPopulate(int i, char* bytes) {
	dataBlocks[i].flag = shortFromBytes(bytes[100*i], bytes[1+100*i]);
	dataBlocks[i].azimuth = shortFromBytes(bytes[2+100*i], bytes[3+100*i]);
	for (int j = 0; j<32; j++) {
		channelDataPopulate(i, j, bytes);
	}

}

void LidarPacket::channelDataPopulate(int i, int j, char* bytes) {
	dataBlocks[i].channelDatas[j].distance = shortFromBytes(bytes[4+(100*i)+(3*j)], bytes[5+(100*i)+(3*j)]);
	dataBlocks[i].channelDatas[j].reflectivity = bytes[6+(100*i)+(3*j)];
}
unsigned short LidarPacket::shortFromBytes(byte a, byte b) {
   return ((unsigned short)b << 8) | a;
}


point3d LidarPacket::cartesianFromSpherical(float r, float rho, float theta, float reflectivity) {
	point3d result;
	result.x = (r * sin(rho * RADIANCONVERT) * cos(theta * RADIANCONVERT));
	result.y = (r * sin(rho * RADIANCONVERT) * sin(theta * RADIANCONVERT));
	result.z = (r * cos(rho * RADIANCONVERT));
	result.reflectivity = reflectivity;
	return result;
}

point3d* LidarPacket::asCartesian() {
	point3d* result = (point3d*) malloc(16 * 12 * (sizeof(point3d)));
	// for each data block
	for(int i = 0; i < 12; i++) {
		// for each channel
		for(int j = 0; j < 16; j++) {
			result[i * 16 + j] = cartesianFromSpherical(dataBlocks[i].channelDatas[j].distance, laserTable[j], dataBlocks[i].azimuth, dataBlocks[i].channelDatas[j].reflectivity);
		}
	}

	return result;
}