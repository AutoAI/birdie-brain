#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <iostream>

#include "LidarPacket.hpp"

#define MAXRECVSTRING 1206  /* Longest string to receive */

typedef unsigned char byte;

void itoa2(char s, char* output) {
    char a = s;
    for(int i = 0; i < 8; i++) {
        if((a & 0x80) >> i) {
            output[i] = '1';
        } else {
            output[i] = '0';
        }
        a <<= 1;
    }
}

void printBinary(char* s) {
    char output[9];
    int i = 0;
    while(*s) {
        itoa2(*s, output);
        printf("%d\t%s\t%x\n", i++, output, (unsigned char)s[0]);
        ++s;
    }
}

int main(int argc, char *argv[]) {
    int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast Address */
    unsigned short broadcastPort;     /* Port */
    char recvString[MAXRECVSTRING+1]; /* Buffer for received string */
    int recvStringLen;                /* Length of received string */


    if (argc != 2) {   /* Test for correct number of arguments */
        fprintf(stderr,"Usage: %s <Broadcast Port>\n", argv[0]);
        exit(1);
    }

    broadcastPort = atoi(argv[1]);   /* First arg: broadcast port */

    /* Create a best-effort datagram socket using UDP */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        perror("socket() failed");

    /* Construct bind structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));            /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                          /* Internet address family */
    broadcastAddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* Any incoming interface */
    broadcastAddr.sin_port = htons(broadcastPort);               /* Broadcast port */

    /* Bind to the broadcast port */
    if (bind(sock, (struct sockaddr *) &broadcastAddr, sizeof(broadcastAddr)) < 0)
        perror("bind() failed");

    /* Receive a single datagram from the server */
    for(int i = 0; i < 100; i++) {
    if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, MSG_WAITALL, NULL, 0)) < 0)
        perror("recvfrom() failed");
    if(recvStringLen != 1206)
    printf("recv len:\t%d\n", recvStringLen);
    }

    recvString[recvStringLen] = '\0';
    //printBinary(recvString);

    LidarPacket* packet = new LidarPacket(&recvString[0]);
    std::cout << "Something = ";
    printf("%u\n", packet->factory);
    delete packet;
    close(sock);
    exit(0);
}
