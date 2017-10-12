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
    int i = 0;

    while(run) {
        printf("Waiting for key input...\n");
        scanf("%x", &cap);
        //link.move(moveit, 1.0, cap);
        link.writeByte(cap & 0xFF);
        if(i++ == 2) {
            i = 0;
            usleep(100000);
            link.readByte(&retval);
            //printf("Retval : %x/n", retval);
            link.readByte(&retval);
            //printf("Retval : %x/n", retval);
            link.readByte(&retval);
            //printf("Retval : %x/n", retval);
            link.readByte(&retval);
            link.readByte(&retval);
            //printf("Retval : %x/n", retval);
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
