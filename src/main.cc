/**
 * File              : src/main.cc
 * Author            : Siddharth J. Singh <j.singh.logan@gmail.com>
 * Date              : 09.08.2017
 * Last Modified Date: 21.08.2017
 * Last Modified By  : Siddharth J. Singh <j.singh.logan@gmail.com>
 */

/**
 * src/main.cc
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

#include <signal.h>
#include <stdio.h>
#include <cmath>

#include "freenect_grabber.h"
#include "ucon_link.h"
#include "gui.h"

#define IRR_ORIGIN      irr::core::vector3df(0, 0, 0)
#define SHAFT_Y_OFFEST  irr::core::vector3df(0, 552.5, 0) 
#define COUPLING_OFFSET irr::core::vector3df(-28.78, 85, 47)
#define RAIL_OFFSET     irr::core::vector3df(0, 495, 0)

#define LEFT_OFFSET     irr::core::vector3df(-28.78, 85, 47)

#define RIGHT_OFFSET    irr::core::vector3df(0, 0, -1300)
#define RIGHT_ROTATION  irr::core::vector3df(0, 180, 0)

#define HORIZ_OFFSET    irr::core::vector3df(0, 120, -126)
#define HORIZ_ROTATION  irr::core::vector3df(90, 180, 0) 

int main() {

    /*signal(SIGINT, signal_hd);
    FreenectGrabber grabber;
    cv::Mat image;
    grabber.grab_image(image);*/
    
    /*signal(SIGINT, signal_hd);
    UConLink link("/dev/ttyUSB0", B4800, "8E2");
    uint32_t cap = 0;
    uint8_t retval;

    link.readByte(&retval);
    while(run) {
        printf("Enter the type of control\n" 
               " 1. LOAD\n"
               " 2. START\n"
               " 3. STOP\n"
               " 4. SCAN\n");
        scanf("%d", &cap);

        if(cap == 1) {
            printf("Enter moveit command(HEX)...\n");
            uint8_t moveit;
            scanf("%x", &cap);
            moveit = cap & 0xFF;

            printf("Enter speed_x (HEX)...\n");
            uint8_t speed_x;
            scanf("%x", &cap);
            speed_x = cap & 0xFF;

            printf("Enter speed_y (HEX)...\n");
            uint8_t speed_y;
            scanf("%x", &cap);
            speed_y = cap & 0xFF;
            
            printf("Enter speed_z (HEX)...\n");
            uint8_t speed_z;
            scanf("%x", &cap);
            speed_z = cap & 0xFF;
            
            printf("Enter x length (DEC)...\n");
            uint32_t len_x;
            scanf("%d", &cap);
            len_x = cap;

            printf("Enter y length (DEC)...\n");
            uint32_t len_y;
            scanf("%d", &cap);
            len_y = cap;

            printf("Enter z length (DEC)...\n");
            uint32_t len_z;
            scanf("%d", &cap);
            len_z = cap;

            link.load(moveit, speed_x, speed_y, speed_z, len_x, len_y, len_z);

        } else if(cap == 2) {
            link.start();
        } else if(cap == 3) {
            link.stop();
        } else if(cap == 4) {
            uint8_t data;
            link.readByte(&data);
            printf("Data Read : %x\n", data);
        }
    }*/

    GUI gui;
    gui.init();

    return 0;
}
