#pragma once

class LidarPacket {
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
    short factory;
}