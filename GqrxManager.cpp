//
// Created by mwolosewicz on 23.07.2020.
//

#include "GqrxManager.h"
#include "ConnectorException.h"
#include "GqrxManagerException.h"

#include <sstream>
#include <string>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::vector;
using std::stringstream;

static constexpr size_t kMaxCommandBuffSize = 128;
static constexpr char kErrorMark[] = "RPRT 1\n";
static char commandBuffer[kMaxCommandBuffSize];

static const map<string, GqrxManager::DemodulatorMode_t> demodulatorModeMap = {
        {"OFF",GqrxManager::DemodulatorMode_t::kOff},
        {"RAW",GqrxManager::DemodulatorMode_t::kRaw},
        {"AM",GqrxManager::DemodulatorMode_t::kAm},
        {"FM",GqrxManager::DemodulatorMode_t::kFm},
        {"WFM",GqrxManager::DemodulatorMode_t::kWfm},
        {"WFM_ST",GqrxManager::DemodulatorMode_t::kWfmSt},
        {"WFM_ST_OIRT",GqrxManager::DemodulatorMode_t::kWfmStOirt},
        {"LSB",GqrxManager::DemodulatorMode_t::kLsb},
        {"USB",GqrxManager::DemodulatorMode_t::kUsb},
        {"CW",GqrxManager::DemodulatorMode_t::kCw},
        {"CWL",GqrxManager::DemodulatorMode_t::kCwl},
        {"CWU",GqrxManager::DemodulatorMode_t::kCwu}
};

GqrxManager::GqrxManager(const Connector &aConnector) noexcept : mConnector(aConnector) {}

void GqrxManager::SetFrequency(freq_t aFreqHz) const {
    snprintf(commandBuffer, kMaxCommandBuffSize, "F %llu\n", aFreqHz);
    try {
        mConnector.Send(string(commandBuffer));
        if (mConnector.Receive() == kErrorMark) {
            throw GqrxManagerException("Can't change frequency. Gqrx error received.");
        }
    } catch (ConnectorException &connectorException) {
        throw GqrxManagerException("Can't change frequency. Problem with connector.");
    }
}

freq_t GqrxManager::GetFrequency() const {
    freq_t currentFrequency = 0;
    char *pEnd = 0;
    try {
        mConnector.Send("f\n");
        string received = mConnector.Receive();
        if (received == kErrorMark) {
            throw GqrxManagerException("Can't get frequency. Gqrx error received.");
        }
        currentFrequency = strtoull(received.c_str(), &pEnd, 10);
    } catch (ConnectorException &connectorException) {
        throw GqrxManagerException("Can't change frequency. Problem with connector.");
    }
    return currentFrequency;
}

void GqrxManager::SetDemodulatorMode(const DemodulatorParam_t aDemodulatorParam) const {

    string demodulatorMode;
    try {
        for (const auto & it : demodulatorModeMap) {
            if (it.second == aDemodulatorParam.mMode) {
                demodulatorMode = it.first;
                break;
            }
        }

        if (demodulatorMode == "") {
            throw GqrxManagerException("Wrong demodulator mode.");
        }

        snprintf(commandBuffer, kMaxCommandBuffSize, "M %s %llu\n", demodulatorMode.c_str(), aDemodulatorParam.mFilterWidth);
        mConnector.Send(commandBuffer);
        if (mConnector.Receive() == kErrorMark) {
            throw GqrxManagerException("Can't change demodulator mode. Gqrx error received.");
        }
    } catch (ConnectorException &connectorException) {
        throw GqrxManagerException("Can't change demodulator mode. Problem with connector.");
    }
}

#include <iostream>

GqrxManager::DemodulatorParam_t GqrxManager::GetDemodulatorMode() const {

    DemodulatorParam_t demodulatorParam {.mMode = GqrxManager::DemodulatorMode_t::kAm, .mFilterWidth = 0};

    try {
        mConnector.Send("m\n");
        string demodulatorMode = mConnector.Receive();
        if (demodulatorMode == kErrorMark) {
            throw GqrxManagerException("Can't get demodulator mode. Gqrx error received.");
        }

        string token;
        vector<string> tokenized;
        stringstream response(demodulatorMode);

        while(getline(response, token, '\n')) {
            tokenized.push_back(token);
        }

        demodulatorParam.mMode = demodulatorModeMap.at(tokenized[0]);

        char* pEnd = nullptr;
        demodulatorParam.mFilterWidth = strtoll(tokenized[1].c_str(), &pEnd, 10);

    } catch (ConnectorException &connectorException) {
        throw GqrxManagerException("Can't get demodulator mode. Problem with connector.");
    } catch (std::out_of_range &out_of_range) {
        throw GqrxManagerException("Can't get demodulator mode. Demodulator mode unknown.");
    }

    return demodulatorParam;
}

float GqrxManager::GetSignalStrength() const {
    float signalStrength = -1.0f;

    try {
        mConnector.Send("l STRENGTH\n");
        string received = mConnector.Receive();
        if (received == kErrorMark) {
            throw GqrxManagerException("Can't get signal strength. Gqrx error received.");
        }
        signalStrength = std::stof(received);

    } catch (ConnectorException &connectorException) {
        throw GqrxManagerException("Can't get signal strength. Problem with connector.");
    }
    return signalStrength;
}

void GqrxManager::SetSquelch(float aSquelch) const {
    snprintf(commandBuffer, kMaxCommandBuffSize, "L SQL %f\n", aSquelch);
    try {
        mConnector.Send(string(commandBuffer));
        if (mConnector.Receive() == kErrorMark) {
            throw GqrxManagerException("Can't change squelch. Gqrx error received.");
        }
    } catch (ConnectorException &connectorException) {
        throw GqrxManagerException("Can't change squelch. Problem with connector.");
    }
}

float GqrxManager::GetSquelch() const {
    float squelch = -1.0f;

    try {
        mConnector.Send("l SQL\n");
        string received = mConnector.Receive();
        if (received == kErrorMark) {
            throw GqrxManagerException("Can't get squelch. Gqrx error received.");
        }
        squelch = std::stof(received);

    } catch (ConnectorException &connectorException) {
        throw GqrxManagerException("Can't get squelch. Problem with connector.");
    }
    return squelch;
}

void GqrxManager::SetRecord(bool aRecord) const {
    snprintf(commandBuffer, kMaxCommandBuffSize, "U RECORD %d\n", aRecord);
    try {
        mConnector.Send(string(commandBuffer));
        if (mConnector.Receive() == kErrorMark) {
            throw GqrxManagerException("Can't change record state. Gqrx error received.");
        }
    } catch (ConnectorException &connectorException) {
        throw GqrxManagerException("Can't change record state. Problem with connector.");
    }
}

bool GqrxManager::GetRecord() const {
    bool recordStatus = false;

    try {
        mConnector.Send("u RECORD\n");
        string received = mConnector.Receive();
        if (received == kErrorMark) {
            throw GqrxManagerException("Can't get record status. Gqrx error received.");
        }
        recordStatus = (std::stoi(received) == 1);

    } catch (ConnectorException &connectorException) {
        throw GqrxManagerException("Can't get record status. Problem with connector.");
    }
    return recordStatus;
}
