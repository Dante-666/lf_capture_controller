/**
 * File              : inc/ucon_link.h
 * Author            : Siddharth J. Singh <j.singh.logan@gmail.com>
 * Date              : 19.09.2017
 * Last Modified Date: 19.09.2017
 * Last Modified By  : Siddharth J. Singh <j.singh.logan@gmail.com>
 */

/**
 * ucon_link.h
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

#ifndef __UCON_LINK_H_
#define __UCON_LINK_H_
#include <stdio.h>
#include <sgtty.h>
#include <stdint.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions          */
#include <errno.h>   /* ERROR Number Definitions           */
#include <spdlog/spdlog.h>

class UConLink {
    public:
        UConLink(const char* port, const int baud, const char* fmt);
        ~UConLink();
        void writeByte(uint8_t data);
        void readByte(uint8_t* data);
    private:
        int fd;
        std::shared_ptr<spdlog::logger> _logger;
};

#endif //__UCON_LINK_H_