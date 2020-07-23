//
// Created by mwolosewicz on 23.07.2020.
//

#ifndef GQRX_CPP_SCANNER_GQRXMANAGEREXCEPTION_H
#define GQRX_CPP_SCANNER_GQRXMANAGEREXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class GqrxManagerException : public std::exception {
public:
    /**
     * Constructor.
     * @param aMessage - the error message.
     */
    explicit GqrxManagerException(std::string aMessage) : mMsg(std::move(aMessage)) {}

    /**
     * Delete no-arg constructor.
     */
    GqrxManagerException() = delete;

    virtual const char* what() const throw () override {
        return mMsg.c_str();
    }

protected:
    std::string mMsg;
};

#endif //GQRX_CPP_SCANNER_GQRXMANAGEREXCEPTION_H
