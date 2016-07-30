#include "LidarPacket.hpp"
#include "point3d.hpp"
#include <math.h>

const float RADIANCONVERT = (3.141592653589 / 180);

LidarPacket::LidarPacket(char* bytes) {
	
	float laserTable [16] = {   RADIANCONVERT * -15,
    	                        RADIANCONVERT * 1,
        	                    RADIANCONVERT * -13,
            	                RADIANCONVERT * -3,
                                RADIANCONVERT * -11,
                   	            RADIANCONVERT * 5,
                       	        RADIANCONVERT * -9,
                           	    RADIANCONVERT * 7,
                               	RADIANCONVERT * -7,
                               	RADIANCONVERT * 9,
                               	RADIANCONVERT * -5,
                               	RADIANCONVERT * 11,
                               	RADIANCONVERT * -3,
                               	RADIANCONVERT * 13,
                               	RADIANCONVERT * -1,
                               	RADIANCONVERT * 15,
    };

	for (int i = 0; i<12; i++) {
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

}
point3d cartesianFromSpherical(float r, float rho, float theta, float reflectivity) {
	point3d result;
	result.x = (r * math.sin(rho) * math.cos(theta));
	result.y = (r * math.sin(rho) * math.sin(theta));
	result.z = (r * math.cos(rho));
	result.reflectivity = reflectivity;
}