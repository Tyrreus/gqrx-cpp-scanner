#include <iostream>

#include "Connector.h"
#include "ConnectorException.h"

using std::cout;
using std::endl;

int main() {

    try {
        Connector connector("127.0.0.1", 7356);

        connector.Send("F 172000000\n");
        cout << "Received: " << connector.Receive() << endl;


    } catch(ConnectorException &connectorException) {
        cout << connectorException.what() << endl;
    }
    return 0;
}
