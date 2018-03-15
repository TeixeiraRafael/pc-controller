#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <vector>

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

#include <alsa/asoundlib.h>
#include <alsa/mixer.h>

using namespace std;

//Serial defaults
const int SERIAL_BAUD_RATE = 9600;
const int SERIAL_BUFFER_SIZE = 8;
const string SERIAL_PORT = "/dev/ttyACM0";

#endif // DEFINITIONS_H
