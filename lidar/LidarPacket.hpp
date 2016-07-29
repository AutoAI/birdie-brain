#pragma once
#include "point3d.hpp"

// class for storing data from one packet from the lidar (refer to VLP-16 manual page 12)
class LidarPacket {
typedef unsigned char byte;
public:
    LidarPacket(char* bytes);
    //~LidarPacket(); 

    // struct for storing data from one channel (1 of the 16 lasers) for one sample
    typedef struct channelData {
        // how far away did the laser hit
        short distance;
        // how strongly did it reflect
        byte reflectivity;
    } channelData;

    // struct for storing one 'block' of data- 2 samples from all channels
    typedef struct dataBlock {
        // this should always be 0xFFEE
        short flag;
        // how far around the first sample is
        short azimuth;
        // samples from each channel, 2 per channel (0-15, then 0-15 again)
        channelData channelDatas[32];
    } dataBlock;

	
    // 12 blocks of data
    dataBlock dataBlocks[12];
    // time when sample was collected (from lidar's clock)
    int timestamp;
    unsigned short factory;
    void packetConvert(point3d*);
 private:
    void dataBlockPopulate(int i, char* bytes);
    void channelDataPopulate(int i, int j, char* bytes);
    unsigned short shortFromBytes(byte a, byte b);
    point3d cartesianFromSpherical(float r, float rho, float theta, float reflectivity);
    float laserTable [16];    
};
