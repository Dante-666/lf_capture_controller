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

UConLink::UConLink(const char* port, int baud, char* fmt) {
    //TODO: do this from a file probably
    __logger()->set_level(spdlog::level::trace);

    this->fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);

    // TODO: handshake mechanism, uC sends message continously
    // untill acknowledged by the PC    
    if(this->fd != 0) {
        __logger()->error("Error in opening serial port %s !!!", port);
        __logger()->error("Check if the USB cable is connected properly to the controller.");
        exit(-1);
    } else {
        __logger()->info("Serial port %s opened sucessfully.", port);
    }

    
}

void UConLink::readByte(uint8_t* data) {
    *data = 1;
}

void UConLink::writeByte(uint8_t data) {}

std::shared_ptr<spdlog::logger> UConLink::__logger() {
    return _logger;
}
