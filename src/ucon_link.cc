/**
 * File              : src/ucon_link.cc
 * Author            : Siddharth J. Singh <j.singh.logan@gmail.com>
 * Date              : 19.09.2017
 * Last Modified Date: 19.09.2017
 * Last Modified By  : Siddharth J. Singh <j.singh.logan@gmail.com>
 */

/**
 * src/ucon_link.cc
 * Copyright (c) 2017 Siddharth J. Singh <j.singh.logan@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ucon_link.h"

UConLink::UConLink(const char* port, const char* baud, const char* fmt) noexcept(false){
    //TODO: do this by reading a enviornment variable
    _logger = spdlog::stdout_color_mt("UConLink");
    _logger->set_level(spdlog::level::trace);

    _logger->trace("Opening file {0}", port);
    this->fd = open(port, O_RDWR | O_NOCTTY);

    if(this->fd == -1) {
        _logger->error("error {0}", errno);
        switch (errno) {
            case EACCES:
                _logger->error("Permission denied, change ownership for {0} and try again.", port);
                break;
            case ENOENT:
                _logger->error("File {0} doesn't exist!!!", port);
                _logger->error("Check if the USB cable is connected properly to the controller.");
                break;

        }
        this->~UConLink();
        throw ucon_link::serial_file_open();
    } else {
        _logger->trace("Serial port {0} opened sucessfully.", port);
    }

    struct termios params;
    memset(&params, 0, sizeof(termios));

    std::string baud_rate = baud;
    
    /*-- If experimenting with a different baud rate, do add things over here --*/
    if(baud_rate == "B4800") {
        cfsetspeed(&params, B4800);
    } else {
        cfsetspeed(&params, B4800);
    }
    _logger->trace("Speed : {0}, {1}", params.c_ispeed, params.c_ospeed);

    unsigned int flag;
    
    if(fmt[1] == 'E')
        flag = PARENB;
    else if(fmt[1] == 'O')
        flag = PARENB | PARODD;
    else {
        _logger->error("Invalid frame format {0}!!!", fmt);
        this->~UConLink();
        throw ucon_link::bad_setting();
    }

    if(fmt[0] == '8')
        flag |= CS8;
    else if(fmt[0] == '7')
        flag |= CS7;
    else if(fmt[0] == '6')
        flag |= CS6;
    else if(fmt[0] == '5')
        flag |= CS5;
    else {
        _logger->error("Invalid frame format {0}!!!", fmt);
        this->~UConLink();
        throw ucon_link::bad_setting();
    }

    if(fmt[2] == '2')
        flag |= CSTOPB;
    else if(fmt[2] != '1') {
        _logger->error("Invalid frame format {0}!!!", fmt);
        this->~UConLink();
        throw ucon_link::bad_setting();
    }
        

    params.c_cflag |= flag;
    _logger->trace("Frame flags : {0}", params.c_cflag);

    if (tcsetattr(this->fd, TCSANOW, &params) != 0) {
        _logger->error("Error in setting termios attributes!!!");
        this->~UConLink();
        throw ucon_link::bad_setting();
    }
    else
        _logger->trace("Baud rate : {0}, Stopbits : {1}, Length : {2}, Parity : {3}", baud, fmt[2], fmt[0], fmt[1]);

}

UConLink::~UConLink() {
    spdlog::drop("UConLink");
    if(this->fd)
        close(this->fd);
}

bool UConLink::checkPort(const char* port) {
    if(access(port, F_OK) == 0) return true;
    else return false;
}

void UConLink::readByte(uint8_t* data) {
    this->readWord(data, 1);
}

void UConLink::readWord(uint8_t* word, uint8_t length) {
    read(this->fd, word, length);
    
    for(int i = 0; i< length; i++)
        _logger->trace("Data read : {0:x}", word[i]);

}

void UConLink::writeByte(uint8_t data) {
    
    _logger->trace("Data written : {0:x}", data);
    
    write(this->fd, &data, 1);
}

void UConLink::writeWord(uint8_t* word, uint8_t length) {

    for(int i = 0; i< length; i++)
        _logger->trace("Data written : {0:x}", word[i]);

    write(this->fd, word, length);
}

void UConLink::start() {
    
    _logger->trace("Starting all the loaded motors.");

    uint8_t retval;
    
    this->writeByte(START);
    usleep(50000);
    this->readByte(&retval);
    
    if(retval != SUCCESS) {
        _logger->error("Main controller is not responding...");
            //TODO: do error handling here later.
            //this->~UConLink();
            //exit(-1);
    }
}

void UConLink::stop() {
    
    _logger->trace("Stopping all the loaded motors.");

    uint8_t retval;
    
    this->writeByte(STOP);
    usleep(50000);
    this->readByte(&retval);
    
    if(retval != SUCCESS) {
        _logger->error("Main controller is not responding...");
            //TODO: do error handling here later.
            //this->~UConLink();
            //exit(-1);
    }
}

void UConLink::load(uint8_t moveit,
                    uint8_t speed_x, uint8_t speed_y, uint8_t speed_z,
                    uint32_t len_x, uint32_t len_y, uint32_t len_z) {

    _logger->trace("Loading motors {0:b} for lengths : {1}, {2}, {3}", moveit, len_x, len_y, len_z);
    
    uint8_t retval;
    uint8_t* command = (uint8_t *) malloc(14);

    command[0] = LOAD;
    command[1] = moveit;
    
    command[2] = speed_x;
    command[3] = speed_y;
    command[4] = speed_z;
    
    command[5] = len_x & 0xFF;
    command[6] = (len_x >> 8) & 0xFF;
    command[7] = (len_x >> 16) & 0xFF;
    
    command[8] = len_y & 0xFF;
    command[9] = (len_y >> 8) & 0xFF;
    command[10] = (len_y >> 16) & 0xFF;
    
    command[11] = len_z & 0xFF;
    command[12] = (len_z >> 8) & 0xFF;
    command[13] = (len_z >> 16) & 0xFF;

    this->writeWord(command, 14);
    usleep(50000);
    this->readByte(&retval);

    if(retval != SUCCESS) {
        _logger->error("Main controller is not responding...");
            //TODO: do error handling here later.
            //this->~UConLink();
            //exit(-1);
    }

    free(command);

}
