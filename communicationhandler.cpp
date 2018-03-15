#include "communicationhandler.h".h"
using namespace boost;

CommunicationHandler::CommunicationHandler(): connection_flag(false), io_svc(), serial(io_svc){
    this->current_volume = 50;
}

CommunicationHandler::~CommunicationHandler(){
    this->disconnect();
}

bool CommunicationHandler::connect(string port){
    try{
        serial.open(port);
        serial.set_option(asio::serial_port_base::baud_rate(SERIAL_BAUD_RATE));
        serial.set_option(asio::serial_port_base::character_size(8));
    } catch(system::system_error e){
        cout << e.what() << endl;
    }

    if(serial.is_open()){
        connection_flag = true;
        reader = std::thread(&CommunicationHandler::readData, this);
    }else{
        cout << "Erro na conexão serial" << endl;
    }
}

bool CommunicationHandler::disconnect(){
    connection_flag = false;
    serial.close();
    reader.join();
}

bool CommunicationHandler::connected(){
    return this->connection_flag;
}

void CommunicationHandler::readData(){
    unsigned char received, last_data;
    boost::system::error_code ec;
    while(connected()){
        serial.read_some(asio::buffer(&received, 1), ec);
        if(received != last_data){
            cout << received << endl;
            if(received == '1'){
                this->setVolume(this->volUp());
            }
            else if(received == '2'){
                this->setVolume(this->volDown());
            }
            last_data = received;
        }
    }
}

long CommunicationHandler::volDown(){
    current_volume = current_volume - pace;
    if(current_volume < 0)
        current_volume = 0;
    return current_volume;
}

long CommunicationHandler::volUp(){
    current_volume = current_volume + pace;
    if(current_volume > 100)
        current_volume = 100;
    return current_volume;
}

void CommunicationHandler::setVolume(long value){
    long min, max;
    snd_mixer_t *handle;
    snd_mixer_selem_id_t *sid;
    const char *card = "default";
    const char *selem_name = "Master";

    snd_mixer_open(&handle, 0);
    snd_mixer_attach(handle, card);
    snd_mixer_selem_register(handle, NULL, NULL);
    snd_mixer_load(handle);

    snd_mixer_selem_id_alloca(&sid);
    snd_mixer_selem_id_set_index(sid, 0);
    snd_mixer_selem_id_set_name(sid, selem_name);
    snd_mixer_elem_t* elem = snd_mixer_find_selem(handle, sid);

    snd_mixer_selem_get_playback_volume_range(elem, &min, &max);

    snd_mixer_selem_set_playback_volume_all(elem, (value * max / 100));

    snd_mixer_close(handle);
}

