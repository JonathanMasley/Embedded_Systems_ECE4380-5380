/*
 * Copyright (c) 2015-2019, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *    ======== udpEcho.c ========
 *    Contains BSD sockets code.
 */

#include "c_header.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <ti/net/slnetutils.h>
#include <ti/ndk/inc/nettools/inc/inet.h>


/* Have to define my own ip_mreq for multicasting since the struct ip_mreq definition is in
 * ti/ndk/inc/socketndk.h which interferes with all the other bullshit included above... */
struct ip_mreq {
     struct in_addr imr_multiaddr; /* Multicast group address */
     struct in_addr imr_interface; /* Local interface address (no clue what this means) */
};

#define UDPPACKETSIZE 1472
#define MAXPORTLEN    6
#define DEFAULT_NET_PORT       1000

extern void     fdOpenSession();
extern void     fdCloseSession();
extern void    *TaskSelf();

extern void     runVoice(char *input);
extern void     runNETUDP(char *input, int32_t binaryCount);
extern char    *getNextInp(char *input, bool printLog);


/* Varies from runNETUDP in that this picks out a good portion of the IP data */
char *parseNETUDP(char *input, struct sockaddr_in *clientAddr, bool parsePayload) {

    char       *loc;
    char       *colon;
    int32_t     addrByte;
    uint32_t    port;

    /* Copy the entire input into loc */
    loc = input;
    if (!loc) {
        return loc;
    }

    /* Checks to see if "localhost" was entered instead of 127.  0.  0.  1 */
    if (strncmpi(loc, "localhost", strlen("localhost")) == 0) {
        clientAddr->sin_addr.s_addr = 0x0100007F;
        goto colonParse;
    }

    /* Checks to see if "broadcast was entered instead of  255.255.255.255 */
    if (strncmpi(loc, "broadcast", strlen("broadcast")) == 0) {
        clientAddr->sin_addr.s_addr = 0xFFFFFFFF;
        goto colonParse;
    }

    /* Checks to see if "nobody" was designated as the IP instead of 0.0.0.0 */
    if (strncmpi(loc, "nobody", strlen("nobody")) == 0) {
        clientAddr->sin_addr.s_addr = 0x00000000;
        goto colonParse;
    }

    /* Checks the first portion of the ip address.      Here.___.___.___ */
    if (isdigit((int)*loc) == 0) {
        putB("Error: Missing required digits.");
        return NULL;
    }
    addrByte = atoi(loc);
    clientAddr->sin_addr.s_addr = addrByte;

    /* Checks the second portion of the IP address.     ___.Here.___.___ */
    loc = strchr(loc, '.');
    if (!loc) {
        return NULL;
    }
    loc++;
    addrByte = atoi(loc);
    clientAddr->sin_addr.s_addr |= addrByte << 8; // clientAddr stores the IPs backwards!

    /* Checks the third portion of the IP address.      ___.___.Here.___ */
    loc = strchr(loc, '.');
    if (!loc) {
        return NULL;
    }
    loc++;
    addrByte = atoi(loc);
    clientAddr->sin_addr.s_addr |= addrByte << 16;


    /* Checks the third portion of the IP address.      ___.___.___.Here */
    loc = strchr(loc, '.');
    if (!loc) {
        return NULL;
    }
    loc++;
    addrByte = atoi(loc);
    clientAddr->sin_addr.s_addr |= addrByte << 24;

/* Colon checking has been implemented but it has not been tested! Should just update port in clientAddr */
colonParse:
    colon = strchr(loc, ':');
    if (!colon) {
        port = DEFAULT_NET_PORT;
        loc = strchr(loc, ' ');
    }
    else {
        loc = colon;
        loc++;
        if (*loc == 0) {
            return loc;
        }

        if (isdigit((int)*loc) == 0) {
            return loc;
        }

        port = (uint32_t)atoi(loc);
    }

    clientAddr->sin_port = htons((uint16_t)port);
    clientAddr->sin_family = AF_INET;

    /* If the parseNETUDP was informed to return the payload (which it is in transmitFunction()) then find the hyphen */
    if (loc) {
        if (parsePayload) {
            loc = strchr(loc, '-');
        }
    }

    return loc;

}



void *transmitFunction(void *arg0) {

    char               *xmitbuf = Global.Buffers.msgBuff;
    int                 bytesSent;
    int                 status;
    int                 server = -1;
    fd_set              writeSet;
    struct sockaddr_in  clientAddr;
    char               *loc;
    int                 allowBroadcast = 1;
    uint32_t            gateKey;
    int                 payloadNext;
    int                 bytesRequested;

    /* Following is from canned examples */
    fdOpenSession(TaskSelf());

    puts("NETUDP Transmit Started.");

    server = socket(AF_INET, SOCK_DGRAM, 0);
    if (server == -1) {
        putB("Error: Socket not created.");
        goto shutdown;
    }

    /* Obtain addresses suitable for binding to */
    status = setsockopt(server, SOL_SOCKET, SO_BROADCAST, (void *) &allowBroadcast, sizeof(allowBroadcast));
    if (status != 0) {
        sprintf(xmitbuf, "Error: getaddrinfo() failed: %s", gai_strerror(status));
        putB(xmitbuf);
        goto shutdown;
    }

    /* CREATION OF THE NETUDP TASK! This task is used to TRANSMIT
     * Not sure if this is necessarily needed because udpEchoHooks
     * creates a pthread for transmitFunction but one was made anyway; in hindsight this is needed because */
    while (1) {

        /* Enter the task. */
        Semaphore_pend(Global.Bios.NETUDPSem, BIOS_WAIT_FOREVER);

        /* From canned example but uses only "writeSet" in this function */
        FD_ZERO(&writeSet);
        FD_SET(server, &writeSet);

        bytesSent = -1;

        /* Enters a GateSwi to access the Global.netudpQueue (don't need GateSwi for this technically BUT...
         * it is needed to increment through the buffer which is part of accessing the queue. */
        gateKey = GateSwi_enter(Global.Bios.NETUDPGateSwi);

        /* Returns the payload from the command and then assigns the IP address to the clientAddr structure */
        loc = parseNETUDP(Global.netudpQueue.netudpPayloads[Global.netudpQueue.netudpReading], &clientAddr, true);

        /* If there is a payload, send a packet of length "bytesRequested"
         *      + which is equal to the payload length and the binaryCount length (if -voice)
         * and send it on the opened server and to "clientAddr" */
        if (loc) {
            bytesRequested = (int)strlen(loc) + 1;
            bytesRequested += Global.netudpQueue.netudpBinaryCount[Global.netudpQueue.netudpReading];

            bytesSent = (int)sendto(server, loc, bytesRequested, 0,
                                    (struct sockaddr *)&clientAddr, sizeof(clientAddr));
        }

        /* Determine new index of the circular buffer even if the payload is invalid */
        payloadNext = Global.netudpQueue.netudpReading + 1;
        if (payloadNext >= MAX_NETUDP_COUNT) {
            payloadNext = 0;
        }

        /* If there is a NULL payload, inform user that UDP parse failed */
        if(!loc) {
            putB("Error: UDP Parse Failed.");
            Global.netudpQueue.netudpReading = payloadNext;
            GateSwi_leave(Global.Bios.NETUDPGateSwi, gateKey);
            continue;
        }

        /* If there were NO BYTES SENT or it DOESN'T MATCH bytesRequested, then the send has failed */
        else if(bytesSent < 0 || bytesSent != bytesRequested) {
            putB("Error: Sendto() failed.");
            Global.netudpQueue.netudpReading = payloadNext;
            GateSwi_leave(Global.Bios.NETUDPGateSwi, gateKey);
            continue;
        }

        /* Use previously determined index to increment the circular buffer */
        Global.netudpQueue.netudpReading = payloadNext;
        GateSwi_leave(Global.Bios.NETUDPGateSwi, gateKey);
    }

shutdown:
    if (server != -1) {
        close(server);
    }

    fdCloseSession(TaskSelf());
    return (NULL);
}




void *receiveFunction(void *arg0) {

    char               *xmitbuf = Global.Buffers.msgBuff;
    int                 bytesRcvd;
    int                 status;
    int                 server = -1;
    fd_set              readSet;
    struct addrinfo     hints;
    struct addrinfo    *res, *p;
    struct sockaddr_in  clientAddr;
    socklen_t           addrlen;
    char                buffer[UDPPACKETSIZE];
    char                portNumber[MAXPORTLEN];
    int32_t             optValue = 1;
    struct ip_mreq      mreq;
    uint16_t            listeningPort = *(uint16_t *)arg0;
//    char               *loc;

    /* FROM CANNED EXAMPLE */
    fdOpenSession(TaskSelf());

    puts("NETUDP Receive is Active:");

    sprintf(portNumber, "%d", listeningPort);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags    = AI_PASSIVE;

    /* Obtain addresses suitable for binding to */
    status = getaddrinfo(NULL, portNumber, &hints, &res);
    if (status != 0) {
        sprintf(xmitbuf, "Error: getaddrinfo() failed: %s", gai_strerror(status));
        putB(xmitbuf);
        goto shutdown;
    }

    for (p = res; p != NULL; p = p->ai_next) {
        server = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (server == -1) {
            continue;
        }

        /* Doing the setsockopt function here on SO_REUSEADDR, according to ChatGPT,
         * allows for unicast and multicast as opposed to just multicast which is established later
         * I have yet to assess the necessity of doing this here */
        setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &optValue, sizeof(optValue));

        status = bind(server, p->ai_addr, p->ai_addrlen);
        if (status != -1) {
            break;
        }

        close(server);
        server = -1;
    }

    if (server == -1) {
        putB("Error: Socket not created.");
        goto shutdown;
    } else if (p == NULL) {
        putB("Error: bind failed.");
        goto shutdown;
    } else {
        freeaddrinfo(res);
        res = NULL;
    }

    /* Join multicast group (only needed if expecting multicast packets) */
    mreq.imr_multiaddr.s_addr = inet_addr("239.255.255.1");
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    setsockopt(server, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));


    do {
        /* FROM CANNED EXAMPLE */
        FD_ZERO(&readSet);
        FD_SET(server, &readSet);
        addrlen = sizeof(clientAddr);
        status = select(server + 1, &readSet, NULL, NULL, NULL);

        if (status > 0 && FD_ISSET(server, &readSet)) {
            bytesRcvd = recvfrom(server, buffer, UDPPACKETSIZE, 0,
                                 (struct sockaddr *)&clientAddr, &addrlen);

            // THE FOLLOWING CODE SECTION WAS USED BECAUSE TWO PACKETS WERE BEING PUT INTO THE SAME "buffer"; not necessary for final implementation
            if (bytesRcvd > 0) {
                buffer[bytesRcvd] = '\0';   // NULL-terminate

                // Check if this buffer contains any -voice commands
                if (strstr(buffer, "-voice") != NULL) {
                    char *current_pos = buffer;
                    char *voice_start;

                    // Look for each "-voice" command in the buffer
                    while ((voice_start = strstr(current_pos, "-voice")) != NULL) {
                        // Find the end of this voice command
                        char *next_voice = strstr(voice_start + 1, "-voice");

                        if (next_voice) {
                            // Temporarily null-terminate this packet
                            char saved_char = *next_voice;
                            *next_voice = '\0';

                            runVoice(voice_start);

                            // Restore and move to next
                            *next_voice = saved_char;
                            current_pos = next_voice;
                        } else {
                            // Last (or only) packet in buffer
                            runVoice(voice_start);
                            break;
                        }
                    }
                }
                else {
                    // Handle non-voice commands
                    sprintf(xmitbuf, "NETUDP %d.%d.%d.%d> %s",
                            (uint8_t)( clientAddr.sin_addr.s_addr        & 0xFF),
                            (uint8_t)((clientAddr.sin_addr.s_addr >> 8)  & 0xFF),
                            (uint8_t)((clientAddr.sin_addr.s_addr >> 16) & 0xFF),
                            (uint8_t)((clientAddr.sin_addr.s_addr >> 24) & 0xFF),
                            buffer);
                    puts(xmitbuf);
                    addPayload(buffer);
                }
            }
        }
    } while (status > 0);

shutdown:

    if (res) {
        freeaddrinfo(res);
    }

    if (server != -1) {
        close(server);
    }

    fdCloseSession(TaskSelf());
    return NULL;
}
