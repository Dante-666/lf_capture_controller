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

//#define WITH_CEGUI

#define IRR_ORIGIN irr::core::vector3df(0, 0, 0)

bool run = true;

void signal_hd(int signum){
    if(signum == SIGINT)
        run = false;
}

void rotate_x(irr::scene::ISceneNode* node, float speed, float delta_t) {
    float delta_rot = speed * delta_t * 180.0/M_PI;
    irr::core::vector3df curr_rot = node->getRotation();
    curr_rot += irr::core::vector3df(0, delta_rot, 0);
    node->setRotation(curr_rot);
} 

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

    // Initializing logger
    std::shared_ptr<spdlog::logger> _logger;
    _logger = spdlog::stdout_color_mt("main");

    _logger->set_level(spdlog::level::trace);

    irr::IrrlichtDevice *device;
    irr::video::IVideoDriver *driver;
    irr::scene::ISceneManager *smgr;
    irr::scene::ICameraSceneNode *cam;
    irr::scene::ILightSceneNode *light;

    _logger->trace("Creating Irrlicht device...");
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

    /*_logger->trace("Adding keymap...");
    irr::SKeyMap keyMap[8];
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = irr::KEY_UP;
    keyMap[1].Action = irr::EKA_MOVE_FORWARD;
    keyMap[1].KeyCode = irr::KEY_KEY_W;

    keyMap[2].Action = irr::EKA_MOVE_BACKWARD;
    keyMap[2].KeyCode = irr::KEY_DOWN;
    keyMap[3].Action = irr::EKA_MOVE_BACKWARD;
    keyMap[3].KeyCode = irr::KEY_KEY_S;
    
    keyMap[4].Action = irr::EKA_STRAFE_LEFT;
    keyMap[4].KeyCode = irr::KEY_LEFT;
    keyMap[5].Action = irr::EKA_STRAFE_LEFT;
    keyMap[5].KeyCode = irr::KEY_KEY_A;
    
    keyMap[6].Action = irr::EKA_STRAFE_RIGHT;
    keyMap[6].KeyCode = irr::KEY_RIGHT;
    keyMap[7].Action = irr::EKA_STRAFE_RIGHT;
    keyMap[7].KeyCode = irr::KEY_KEY_D;
    
    _logger->trace("Adding camera and light node...");
    cam = smgr->addCameraSceneNodeFPS(smgr->getRootSceneNode(),
                                      10.f,
                                      .1f,
                                      0,
                                      keyMap,
                                      8,
                                      false,
                                      0.f,
                                      false,
                                      true);*/
    cam = smgr->addCameraSceneNodeMaya(smgr->getRootSceneNode());
    cam->setFOV(2.0f);
    light = smgr->addLightSceneNode();
    //light->setLightType(irr::video::ELT_DIRECTIONAL);
    light->setPosition(irr::core::vector3df(0, 10, 50));

    _logger->trace("Adding meshes...");
    irr::scene::IAnimatedMesh* test = smgr->getMesh("data/meshes/rotor_s.3ds");
    irr::scene::ISceneNode* tnode = smgr->addAnimatedMeshSceneNode(test);
    tnode->setScale(irr::core::vector3df(1.f, 1.f, 1.f));
    cam->setTarget(irr::core::vector3df(4, 45, 0));


    //irr::scene::IAnimatedMesh* test_2 = smgr->getMesh("data/meshes/cube.obj");
    //irr::scene::ISceneNode* tnode_2 = smgr->addAnimatedMeshSceneNode(test_2);
    //irr::scene::ISceneNode* tnode_3 = smgr->addAnimatedMeshSceneNode(test_2);
    //tnode_3->setPosition(irr::core::vector3df(0, 0, 10));

    irr::scene::IAnimatedMesh* test_3 = smgr->getMesh("data/meshes/base.3ds");
    irr::scene::ISceneNode *tnode_4 = smgr->addAnimatedMeshSceneNode(test_3);
    
    irr::scene::IAnimatedMesh* test_4 = smgr->getMesh("data/meshes/rail_s.3ds");
    irr::scene::ISceneNode *tnode_5 = smgr->addAnimatedMeshSceneNode(test_4);

#ifdef WITH_CEGUI
    _logger->trace("Bootstrapping the GUI system...");
    CEGUI::IrrlichtRenderer& guiRend = CEGUI::IrrlichtRenderer::bootstrapSystem(*device);

    _logger->trace("Adding GUI resources...");
    CEGUI::DefaultResourceProvider* guiRP = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
    guiRP->setResourceGroupDirectory("schemes", "data/schemes");
    guiRP->setResourceGroupDirectory("imagesets", "data/imagesets");
    guiRP->setResourceGroupDirectory("fonts", "data/fonts");
    guiRP->setResourceGroupDirectory("layouts", "data/layouts");
    guiRP->setResourceGroupDirectory("looknfeel", "data/looknfeel");
    guiRP->setResourceGroupDirectory("lua_scripts", "data/lua_scripts");
    guiRP->setResourceGroupDirectory("schemas", "data/xml_schemas");
    guiRP->setResourceGroupDirectory("animations", "data/animations");

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
    CEGUI::Font::setDefaultResourceGroup("fonts");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
    CEGUI::AnimationManager::setDefaultResourceGroup("animations");

    CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
    if(parser->isPropertyPresent("SchemaDefaultResourceGroup"))
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");

    CEGUI::SchemeManager::getSingleton().createFromFile("Generic.scheme");
    CEGUI::SchemeManager::getSingleton().createFromFile("GameMenu.scheme");

    _logger->trace("Adding a GUI windowManager...");
    CEGUI::WindowManager& guiWmgr = CEGUI::WindowManager::getSingleton();
    
    CEGUI::Window* guiRoot = guiWmgr.loadLayoutFromFile("GameMenu.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(guiRoot);

    CEGUI::AnimationManager& guiAnimgr = CEGUI::AnimationManager::getSingleton();
    guiAnimgr.loadAnimationsFromXML("GameMenu.anims");

    CEGUI::AnimationInstance* guiStartButtAnimInst = guiAnimgr.instantiateAnimation("StartButtonPulsating");
    CEGUI::Window* guiStartButtWin = guiRoot->getChild("InnerPartContainer/InsideStartClickArea/StartButtonImage"); 
    guiStartButtAnimInst->setTargetWindow(guiStartButtWin);
    guiStartButtAnimInst->start();
    
    CEGUI::AnimationInstance* guiInsideImg1AnimInst = guiAnimgr.instantiateAnimation("InsideImage1Pulsating");
    CEGUI::Window* guiInsideImg1Win = guiRoot->getChild("InnerPartContainer/InsideImage1"); 
    guiInsideImg1AnimInst->setTargetWindow(guiInsideImg1Win);
    guiInsideImg1AnimInst->start();
    
    CEGUI::AnimationInstance* guiTopBarAnimInst = guiAnimgr.instantiateAnimation("TopBarMoveInAnimation");
    CEGUI::Window* guiTopBarWin = guiRoot->getChild("TopBar"); 
    guiTopBarAnimInst->setTargetWindow(guiTopBarWin);
    guiTopBarAnimInst->start();

    CEGUI::AnimationInstance* guiBotBarAnimInst = guiAnimgr.instantiateAnimation("BotBarMoveInAnimation");
    CEGUI::Window* guiBotBarWin = guiRoot->getChild("BotBar"); 
    guiBotBarAnimInst->setTargetWindow(guiBotBarWin);
    guiBotBarAnimInst->start();
#endif
    
    _logger->trace("Entering event loop...");
    uint32_t neo = 0, old, delta;
    float_t delta_f;
    while(device->run()) {
        old = neo;
        neo = device->getTimer()->getTime();
        delta = neo-old;
        delta_f = delta/1000.0;
        if(device->isWindowActive())
        {
            driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
            smgr->drawAll();

#ifdef WITH_CEGUI
            CEGUI::System::getSingleton().renderAllGUIContexts();
            CEGUI::System::getSingleton().injectTimePulse(delta_f);
#endif
            rotate_x(tnode, 6.25*M_PI , delta_f);

            driver->endScene();
        }
        else
            device->yield();
    }

#ifdef WITH_CEGUI
    CEGUI::System::destroy();
    CEGUI::IrrlichtRenderer::destroy(guiRend);
#endif

    _logger->trace("Exiting...");

    return 0;
}
