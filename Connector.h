//
// Created by mwolosewicz on 23.07.2020.
//

#ifndef GQRX_CPP_SCANNER_CONNECTOR_H
#define GQRX_CPP_SCANNER_CONNECTOR_H

#include <string>

/**
 * Class is used as connector to GQRX remote API.
 */
class Connector {
public:

    /**
     * Delete no-arg constructor.
     */
    Connector() = delete;

    /**
     * Destructor.
     */
    virtual ~Connector();

    /**
     * Constructor.
     *
     * Creates connection and connect to server.
     *
     * @param aHostIp - address of host to connect.
     * @param aPort - port which wille be used to connect.
     *
     * @throws ConnectorException if can't create connection.
     */
    Connector(std::string aHostIp, int aPort);

    /**
     * Send data.
     * @param aData data which will be send.
     * @throws ConnectorException if can't send data.
     */
    void Send(const std::string &aData) const;

    /**
     * Receive data.
     * @return received string.
     *
     * @throws ConnectorException if can't receive data.
     */
    std::string Receive() const;

private:
    static constexpr int kRecvBuffMaxSize = 1024;

    int mSock = 0;

    std::string mHostIp;
    int mPort = 0;

};


#endif //GQRX_CPP_SCANNER_CONNECTOR_H
