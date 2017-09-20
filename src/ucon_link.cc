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
    this->fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);

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

    _logger->trace("Speed : {0}, {1}", params.c_ispeed, params.c_ospeed);
    
    cfsetspeed(&params, B500000);

    _logger->trace("Speed : {0}, {1}", params.c_ispeed, params.c_ospeed);

}

UConLink::~UConLink() {
    if(this->fd)
        close(this->fd);
}

void UConLink::readByte(uint8_t* data) {
    *data = 1;
}

void UConLink::writeByte(uint8_t data) {}

