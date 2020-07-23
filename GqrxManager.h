//
// Created by mwolosewicz on 23.07.2020.
//

#ifndef GQRX_CPP_SCANNER_GQRXMANAGER_H
#define GQRX_CPP_SCANNER_GQRXMANAGER_H

#include "Connector.h"

typedef unsigned long long freq_t;

/**
 * Class contains set of methods which can be used for GQRX remote API.
 */
class GqrxManager {
public:

    enum class DemodulatorMode_t {
        kOff,
        kRaw,
        lAm,
        kFm,
        kWfm,
        kWfmSt,
        kWfmStOirt,
        kLsb,
        kUsb,
        kCw,
        kCwl,
        kCwu
    };

    /**
     * Delete default constructor.
     */
    GqrxManager() = delete;

    /**
     * Constructor.
     *
     * @param aConnector connector which will be used for communication.
     */
    explicit GqrxManager(const Connector &aConnector) noexcept;

    /**
     * Set specific frequency.
     *
     * @param aFreq frequency in HZ.
     * @throws GqrxManagerException if error.
     */
    void SetFrequency(freq_t aFreqHz) const;

    /**
     * Get current frequency.
     *
     * @return current frequency.
     * @throws GqrxManagerException if error.
     */
    freq_t GetFrequency() const;

    /**
     * Set demodulator mode.
     *
     * @param aDemodulatorMode mode for demodulator.
     * @throws GqrxManagerException if error.
     */
    void SetDemodulatorMode(DemodulatorMode_t aDemodulatorMode) const;

    /**
     * Get demodulator mode.
     *
     * @return current demodulator mode.
     * @throws GqrxManagerException if error.
     */
    DemodulatorMode_t GetDemodulatorMode() const;

    /**
     * Get signal strength.
     *
     * @return signal strength in dBFS units.
     * @throws GqrxManagerException if error.
     */
    int GetSignalStrength() const;

    /**
     * Set squelch threshold.
     *
     * @param aSquelch threshold in dBFS units.
     * @throws GqrxManagerException if error.
     */
    void SetSquelch(int aSquelch) const;

    /**
     * Get squelch threshold.
     *
     * @return current squelch threshold.
     * @throws GqrxManagerException if error.
     */
    int GetSquelch() const;

    /**
     * Set record state.
     *
     * @param aRecord if true - start record, false stop record.
     * @throws GqrxManagerException if error.
     */
    void SetRecord(bool aRecord) const;

    /**
     * Get current record state.
     *
     * @return current record state.
     * @throws GqrxManagerException if error.
     */
    bool GetRecord() const;

    /**
     * Tell GQRX to close current connection.
     * @throws GqrxManagerException if error.
     */
    void CloseRemoteConnection() const;

private:
    const Connector &mConnector;
};


#endif //GQRX_CPP_SCANNER_GQRXMANAGER_H
