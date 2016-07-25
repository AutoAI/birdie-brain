#pragma once

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
        channelData chanelDataArraySomeoneShouldNameThis[32];
    } dataBlock;

    // 42-byte header because that's what the manual says
    byte header[42];
	
    // 12 blocks of data
    dataBlock dataBlocks[12];
    // time when sample was collected (from lidar's clock)
    int timestamp;
    unsigned short factory;

 private:
    void dataBlockPopulate(int i, char* bytes);
    void channelDataPopulate(int i, int j, char* bytes);
    unsigned short shortFromBytes(byte a, byte b);
};
