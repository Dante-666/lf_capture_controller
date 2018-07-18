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

#include <exception>
#include <spdlog/spdlog.h>

#define START       13
#define LOAD        17
#define SUCCESS     19
#define FAILURE     23
#define STOP        29
#define MOTOR        31

#define X_F         0x01
#define Y_F         0x04
#define Z_F         0x10
#define X_B         0x02
#define Y_B         0x08
#define Z_B         0x20

#define MAX_LEN_X   64000
#define MAX_LEN_Y   64000
#define MAX_LEN_Z   64000

namespace ucon_link {
    struct serial_file_open : public std::exception {
        const char* what() const throw () {
            return "Unable to open the serial port successfully";
        }
    };

    struct bad_setting : public std::exception {
        const char* what() const throw () {
            return "Something was wrong with the file opening settings";
        }
    };
};

class UConLink {
    public:
        UConLink(const char* port, const char* baud, const char* fmt) noexcept(false);
        ~UConLink();

        static bool checkPort(const char* port);
        // TODO: Do IO error handling over here
        // Always allocate memory before sending it off here
        void writeByte(uint8_t data);
        void writeWord(uint8_t* word, uint8_t length);
        void readByte(uint8_t* data);
        void readWord(uint8_t* word, uint8_t length);
        // TODO: Must be built with exception handling
        // to avoid overrunning the motor positions
        // remove the dummy part later.
        // TODO: Better idea to make it blocking so that
        // error values can be transmitted.
        // TODO: Check for the minimum value of lengths for motion
        void load(uint8_t moveit,
                  uint8_t speed_x,
                  uint8_t speed_y,
                  uint8_t speed_z,
                  uint32_t len_x = 0, 
                  uint32_t len_y = 0, 
                  uint32_t len_z = 0);
        void start();
        void stop();
    private:
        int fd = 0;
        std::shared_ptr<spdlog::logger> _logger;
};

#endif //__UCON_LINK_H_
