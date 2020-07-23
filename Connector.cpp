//
// Created by mwolosewicz on 23.07.2020.
//

#include "Connector.h"

#include <arpa/inet.h>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <utility>

#include "ConnectorException.h"

using std::string;
using std::move;
using std::memset;

Connector::Connector(string aHostIp, int aPort) : mHostIp(move(aHostIp)), mPort(aPort) {

    struct sockaddr_in serverAddress;

    mSock = socket(AF_INET, SOCK_STREAM, 0);
    if (mSock < 0) {
        throw ConnectorException("Can't open socket!");
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(mPort);

    if(inet_pton(AF_INET, mHostIp.c_str(), &serverAddress.sin_addr) <= 0) {
        string msg = "Invalid address: ";
        msg.append(mHostIp);
        throw ConnectorException(msg);
    }

    if (connect(mSock, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
        throw ConnectorException("Connection failed");
    }
}

Connector::~Connector() {
    close(mSock);
}

void Connector::Send(const std::string &aData) const {

    int sendDataCount = write(mSock, aData.c_str(), aData.length());
    if (sendDataCount < 0) {
        throw ConnectorException("Error writing to socket");
    }
}

string Connector::Receive() const {
    char recvBuffer[kRecvBuffMaxSize] {};

    int receivedDataCount = read(mSock, recvBuffer, kRecvBuffMaxSize);
    if (receivedDataCount < 0) {
        throw ConnectorException("Error reading from socket");
    }
    recvBuffer[receivedDataCount] = 0;

    return string(recvBuffer);
}
