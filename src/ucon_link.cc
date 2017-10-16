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

UConLink::UConLink(const char* port, const int baud, const char* fmt) {
    //TODO: do this from a file probably
    _logger = spdlog::stdout_color_mt("UConLink");
    _logger->set_level(spdlog::level::trace);

    _logger->trace("Opening file {0}", port);
    this->fd = open(port, O_RDWR | O_NOCTTY);// | O_NDELAY);

    // TODO: handshake mechanism, uC sends message continously
    // untill acknowledged by the PC    
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
        exit(-1);
    } else {
        _logger->trace("Serial port {0} opened sucessfully.", port);
    }

    struct termios params;
    memset(&params, 0, sizeof(termios));

    cfsetspeed(&params, baud);
    _logger->trace("Speed : {0}, {1}", params.c_ispeed, params.c_ospeed);

    unsigned int flag;
    
    if(fmt[1] == 'E')
        flag = PARENB;
    else if(fmt[1] == 'O')
        flag = PARENB | PARODD;
    else {
        _logger->error("Invalid frame format {0}!!!", fmt);
        this->~UConLink();
        exit(-1);
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
        exit(-1);
    }

    if(fmt[2] == '2')
        flag |= CSTOPB;
    else if(fmt[2] != '1') {
        _logger->error("Invalid frame format {0}!!!", fmt);
        this->~UConLink();
        exit(-1);
    }
        

    params.c_cflag |= flag;
    _logger->trace("Frame flags : {0}", params.c_cflag);

    if (tcsetattr(this->fd, TCSANOW, &params) != 0) {
        _logger->error("Error in setting termios attributes!!!");
        this->~UConLink();
        exit(-1);
    }
    else
        _logger->trace("Baud rate : {0}, Stopbits : {1}, Length : {2}, Parity : {3}", baud, fmt[2], fmt[0], fmt[1]);

}

UConLink::~UConLink() {
    if(this->fd)
        close(this->fd);
}

void UConLink::readByte(uint8_t* data) {
    this->readWord(data, 1);

    _logger->trace("Data read : {0:x}", *data);
}

void UConLink::readWord(uint8_t* data, uint8_t length) {
    read(this->fd, data, length);
}

void UConLink::writeByte(uint8_t data) {
    
    _logger->trace("Data written : {0:x}", data);
    
    write(this->fd, &data, 1);
}

void UConLink::writeWord(uint8_t* word, uint8_t length) {

    _logger->trace("Data written : {0:x}", word);

    write(this->fd, word, length);
}

void UConLink::start() {
    
    _logger->trace("Commencing the drive operation.");

    // TODO: Make this to be blocking operation and make the
    // thread wait for this to complete
    this->writeByte(START);

}

void UConLink::stop() {
    
    _logger->trace("Stopping all motors");
    this->writeByte(STOP);
}

void UConLink::load(uint8_t moveit, double length) {

    _logger->trace("Loading {0:b} for length : {1}", moveit, length);
    
    uint8_t retval;
    uint8_t* command = (uint8_t *) malloc(6);

    // TODO: do complex control in the uController itself.
    // There is a lot of memory space available over there

    if(moveit & X_F) {
        command[0] = LOAD;
        if(moveit & (X_B ^ X_F))
            command[1] = X_B;
        else
            command[1] = X_F;
        command[2] = 0x10;    //Freq
        command[3] = 0;    //low count
        command[4] = 250;  //high count
        command[5] = 0;    //no. of 10 rotations
        
        this->writeWord(command, 6);
        this->readByte(&retval);
        
        if(retval != SUCCESS) {
            if(retval == FAILURE) _logger->error("Motor X controller is not responding...");
            else _logger->error("Main controller is not responding...");
            //TODO: do error handling here later.
            this->~UConLink();
            exit(-1);
        }
    }

    if(moveit & Y_F) {
        command[0] = LOAD;
        if(moveit & (Y_B ^ Y_F))
            command[1] = Y_B;
        else
            command[1] = Y_F;
        command[2] = 0x10;    //Freq
        command[3] = 0;    //no. of 10 rotations
        command[4] = 250;
        command[5] = 0;
        
        this->writeWord(command, 6);
        this->readByte(&retval);
        
        if(retval != SUCCESS) {
            if(retval == FAILURE) _logger->error("Motor Y controller is not responding...");
            else _logger->error("Main controller is not responding...");
            //TODO: do error handling here later.
            this->~UConLink();
            exit(-1);
        }
    }
    
    if(moveit & Z_F) {
        command[0] = LOAD;
        if(moveit & (Z_B ^ Z_F))
            command[1] = Z_B;
        else
            command[1] = Z_F;
        command[2] = 0x10;    //Freq
        command[3] = 0;    //no. of 10 rotations
        command[4] = 250;
        command[5] = 0;
        
        this->writeWord(command, 6);
        this->readByte(&retval);
        
        if(retval != SUCCESS) {
            if(retval == FAILURE) _logger->error("Motor Z controller is not responding...");
            else _logger->error("Main controller is not responding...");
            //TODO: do error handling here later.
            this->~UConLink();
            exit(-1);
        }
    }

    free(command);

}
