#include <iostream>

#include "Connector.h"
#include "ConnectorException.h"
#include "GqrxManager.h"
#include "GqrxManagerException.h"

#include <string>

using std::cout;
using std::endl;

using std::string;

int main() {

    try {
        Connector connector("127.0.0.1", 7356);
        GqrxManager gqrxManager(connector);

        gqrxManager.SetFrequency(170000000);
        cout << "Curr freq: " << gqrxManager.GetFrequency() << endl;

    } catch(ConnectorException &connectorException) {
        cout << "Connection exception: " << connectorException.what() << endl;
    } catch(GqrxManagerException &gqrxManagerException) {
        cout << "GQRX manager exception: " << gqrxManagerException.what() << endl;
    }

    return 0;
}
