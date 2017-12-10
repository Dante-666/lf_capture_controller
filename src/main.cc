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
#include "gui.h"

bool run = true;

void signal_hd(int signum){
    if(signum == SIGINT)
        run = false;
}

int main() {

    /*signal(SIGINT, signal_hd);
    FreenectGrabber grabber;
    cv::Mat image;
    grabber.grab_image(image);*/
    
    signal(SIGINT, signal_hd);
    UConLink link("/dev/ttyUSB0", B4800, "8E2");
    uint32_t cap = 0;
    uint8_t retval;

    link.readByte(&retval);
    while(run) {
        /*printf("CONTROL");
        scanf("%d", &cap);
        link.writeByte(cap & 0xFF);*/
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
    }

    /*irr::IrrlichtDevice *device;
    irr::video::IVideoDriver *driver;
    irr::scene::ISceneManager *smgr;
    irr::scene::ICameraSceneNode *cam;

    device = irr::createDevice(irr::video::EDT_OPENGL, 
                               irr::core::dimension2d<irr::u32>(800, 600),
                               32, false, false, false, 0);
    device->setWindowCaption(L"Cartesian Controller");

    driver = device->getVideoDriver();
    driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);
    driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_16_BIT, false);
    driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
    driver->setAmbientLight(irr::video::SColor(255, 255, 255, 255));

    smgr = device->getSceneManager();

    cam = smgr->addCameraSceneNode(smgr->getRootSceneNode(),
                                   irr::core::vector3df(0, 0, 0),
                                   irr::core::vector3df(0, 0, 1),
                                   1, true);
    cam->setFOV(2.0f);

    while(device->run()) {
        if(device->isWindowActive())
        {
            driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
            smgr->drawAll();
            driver->endScene();
        }
        else
            device->yield();
    }
    */

    return 0;
}
