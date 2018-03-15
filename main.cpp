#include "definitions.h"
#include "communicationhandler.h"
int main()
{
    CommunicationHandler c;

    cout << "Connecting to the remote control..." << endl;
    c.connect();

    if(c.connected())
         cout << "Connected!" << endl;
    while(c.connected());

    cout << "Remote control disconnected!" << endl;
}
