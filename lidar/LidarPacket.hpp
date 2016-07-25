#pragma once

class LidarPacket {
public:
    LidarPacket(byte* bytes);
    ~LidarPacket();

    typedef struct channelData {
        short distance;
        byte reflectivity;
    } channelData;

    typedef struct dataBlock {
        short flag;
        short azimuth;
        struct channelData[32];
    } dataBlock;

    byte[42] header;
    dataBlock[12] dataBlocks;
    int timestamp;
    unsigned short factory;

 private:
    void dataBlockPopulate(int i, byte* bytes);
    void channelDataPopulate(int i, intj, byte* bytes);
    unsigned short shortFromBytes(byte a, byte b);


}