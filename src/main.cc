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

#include "freenect_grabber.h"
#include "ucon_link.h"

bool run = true;

void signal_hd(int signum){
    if(signum == SIGINT)
        run = false;
}

int main() {

    signal(SIGINT, signal_hd);

    //FreenectGrabber grabber;
    //cv::Mat image;
    //grabber.grab_image(image);
    
    UConLink link("/dev/ttyUSB1", 500000, "8E2");
    uint8_t data = 1;
    unsigned int cap;

    while(run) {
        scanf("%x", &cap);
        data = 0xFF & cap;
        link.writeByte(data);
    }
    
    return 0;
}
