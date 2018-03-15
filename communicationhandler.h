#ifndef COMMUNICATIONHANDLER_H
#define COMMUNICATIONHANDLER_H
#include "definitions.h"

class CommunicationHandler
{

private:
    bool connection_flag;
    long current_volume;
    long pace = 1;

    std::thread reader;
    boost::asio::io_service io_svc;
    boost::asio::serial_port serial;

    void readData();
    void parseData(vector<unsigned char> received_data);

    long volUp();
    long volDown();
    void setVolume(long volume);

public:
    CommunicationHandler();
    ~CommunicationHandler();

    bool connect(string port = SERIAL_PORT);
    bool disconnect();
    bool connected();
};

#endif // COMMUNICATIONHANDLER_H
