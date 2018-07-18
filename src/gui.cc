/**
 * File              : src/gui.cc
 * Author            : Siddharth J. Singh <j.singh.logan@gmail.com>
 * Date              : 12.12.2017
 * Last Modified Date: 12.12.2017
 * Last Modified By  : Siddharth J. Singh <j.singh.logan@gmail.com>
 */
/**
 * gui.cc
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

#include "gui.h"
#include <iostream>

Settings::Settings() {
    _logger = spdlog::stdout_color_mt("Settings");
    _logger->set_level(spdlog::level::trace);
    _logger->trace("Constructing Settings");
    try {
        this->cfg_file.open("./data/settings.ini");
        std::string line;
        readData();
    } catch (std::ifstream::failure e) {
        _logger->error("There was an error in opening settings.ini, please check the data directory...");
        exit(-1);
    }

}

Settings::~Settings() {
    this->writeback();
    this->cfg_file.close();
    spdlog::drop("Settings");
}

void Settings::readData() {
    _logger->trace("Reading the values from settings.ini...");
    this->cfg_file.seekg(0, std::ios::beg);
    std::string line;
    int splitter;
    //Discard the first line
    cfg_file >> line;
    //Serial Port
    cfg_file >> line;
    splitter = line.find('=');
    this->setSerialPort(line.substr(splitter+1, line.length()));
    //Baud
    cfg_file >> line;
    splitter = line.find('=');
    this->setBaud(line.substr(splitter+1, line.length()));
    //Format
    cfg_file >> line;
    splitter = line.find('=');
    this->setFormat(line.substr(splitter+1, line.length()));
    //X-Axis Speed
    cfg_file >> line;
    splitter = line.find('=');
    this->setSpeedX(std::stof(line.substr(splitter+1, line.length())));
    //Y-Axis Speed
    cfg_file >> line;
    splitter = line.find('=');
    this->setSpeedY(std::stof(line.substr(splitter+1, line.length())));
    //Z-Axis Speed
    cfg_file >> line;
    splitter = line.find('=');
    this->setSpeedZ(std::stof(line.substr(splitter+1, line.length())));
    //X-Axis Travel 
    cfg_file >> line;
    splitter = line.find('=');
    this->setLengthX(std::stof(line.substr(splitter+1, line.length())));
    //Y-Axis Travel 
    cfg_file >> line;
    splitter = line.find('=');
    this->setLengthY(std::stof(line.substr(splitter+1, line.length())));
    //Z-Axis Travel 
    cfg_file >> line;
    splitter = line.find('=');
    this->setLengthZ(std::stof(line.substr(splitter+1, line.length())));

    cfg_file >> line;
    cfg_file >> line;
    splitter = line.find('=');
    this->setGridX(std::stoi(line.substr(splitter+1, line.length())));
    cfg_file >> line;
    splitter = line.find('=');
    this->setGridY(std::stoi(line.substr(splitter+1, line.length())));
    cfg_file >> line;
    splitter = line.find('=');
    this->setGridZ(std::stoi(line.substr(splitter+1, line.length())));
}

void Settings::writeback() {
    _logger->trace("Updating settings.ini for later use...");
    this->cfg_file.seekg(0, std::ios::beg);
    cfg_file << "[Serial_Comm_Options]\n";
    cfg_file << "serial_port=" << this->getSerialPort() << "\n";
    cfg_file << "baud=" << this->getBaud() << "\n";
    cfg_file << "format=" << this->getFormat() << "\n";
    cfg_file << "x_axis_speed=" << this->getSpeedX() << "\n";
    cfg_file << "y_axis_speed=" << this->getSpeedY() << "\n";
    cfg_file << "z_axis_speed=" << this->getSpeedZ() << "\n";
    cfg_file << "x_axis_travel=" << this->getLengthX() << "\n";
    cfg_file << "y_axis_travel=" << this->getLengthY() << "\n";
    cfg_file << "z_axis_travel=" << this->getLengthZ() << "\n";
    cfg_file << "\n[Trajectory_Settings]\n";
    cfg_file << "x_grid=" << this->getGridX() << "\n";
    cfg_file << "y_grid=" << this->getGridY() << "\n";
    cfg_file << "z_grid=" << this->getGridZ() << "\n";
}

void Settings::setSerialPort(std::string port) {
    this->serial_port = port;
}

void Settings::setBaud(std::string baud) {
    this->baud = baud;
}

void Settings::setFormat(std::string format) {
    this->format = format;
}

void Settings::setSpeedX(float speed) {
    this->x_axis_speed = speed;
}

void Settings::setSpeedY(float speed) {
    this->y_axis_speed = speed;
}

void Settings::setSpeedZ(float speed) {
    this->z_axis_speed = speed;
}

void Settings::setLengthX(float length) {
    this->x_axis_length = length;
}

void Settings::setLengthY(float length) {
    this->y_axis_length = length;
}

void Settings::setLengthZ(float length) {
    this->z_axis_length = length;
}

void Settings::setGridX(int size) {
    this->x_grid = size;
}

void Settings::setGridY(int size) {
    this->y_grid = size;
}

void Settings::setGridZ(int size) {
    this->z_grid = size;
}

std::string Settings::getSerialPort() {
    return this->serial_port;
}

std::string Settings::getBaud() {
    return this->baud;
}

std::string Settings::getFormat() {
    return this->format;
}

float Settings::getSpeedX() {
    return this->x_axis_speed;
}

float Settings::getSpeedY() {
    return this->y_axis_speed;
}

float Settings::getSpeedZ() {
    return this->z_axis_speed;
}

float Settings::getLengthX() {
    return this->x_axis_length;
}

float Settings::getLengthY() {
    return this->y_axis_length;
}

float Settings::getLengthZ() {
    return this->z_axis_length;
}

int Settings::getGridX() {
    return this->x_grid;
}

int Settings::getGridY() {
    return this->y_grid;
}

int Settings::getGridZ() {
    return this->z_grid;
}

std::string Settings::ftos(float input) {
    std::stringstream temp;
    temp << std::fixed << std::setprecision(3) << input;
    return temp.str();
}

std::string Settings::itos(int input) {
    return std::to_string(input);
}

GUI::GUI() {
    _logger = spdlog::stdout_color_mt("GUI");
    _logger->set_level(spdlog::level::trace);
    this->initFrequencyLookup();

    _logger->trace("Initialising the GUI framework");

    _logger->trace("Creating Irrlicht device...");
    this->device = irr::createDevice(irr::video::EDT_OPENGL, 
                               irr::core::dimension2d<irr::u32>(1600, 900),
                               32, true, false, false, this);
    this->device->setWindowCaption(L"Cartesian Controller");

    this->driver = this->device->getVideoDriver();
    this->driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_32_BIT, true);
    this->driver->setTextureCreationFlag(irr::video::ETCF_ALWAYS_16_BIT, false);
    this->driver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, true);
    this->driver->setAmbientLight(irr::video::SColor(255, 255, 255, 255));

    this->smgr = this->device->getSceneManager();
    this->cursor = this->device->getCursorControl();
    
    _logger->trace("Hiding mouse cursor...");
    this->cursor = this->device->getCursorControl();
    //this->cursor->setActiveIcon(irr::gui::ECI_CROSS);
    this->cursor->setVisible(false);
    /*this->cegui_cursor = new irr::gui::IGUISpriteBank();
    this->cegui_cursor->addTexture(this->driver->getTexture("data/imagesets/GameMenu.png"));
    this->cegui_icon = new irr::gui::SCursorSprite(this->cegui_cursor, 0, irr::core::position2di(1983, 202));
    this->device->getCursorControl()->addIcon(*(this->cegui_icon));*/

    this->addShaders();
    this->addLightsandCameras();
    this->addShaders();
    this->addMeshes();
    this->createFrame();

    this->bootstrapCEGUI();

    /*-- Create the connection link --*/
    this->openSerialPort();

    /*-- Create the data grabber --*/
}

void GUI::init() {
    _logger->trace("Initializing event loop...");
    uint32_t neo = 0, old, delta;
    float_t delta_t;

    uint32_t port_check_t = 0;
    
    irr::gui::IGUIEnvironment* guienv = device->getGUIEnvironment();

    irr::gui::IGUIFont *font = guienv->getFont("data/fonts/fontlucida.png");

    while(device->run()) {
        old = neo;
        neo = device->getTimer()->getTime();
        delta = neo-old;
        delta_t = delta/1000.0;

        port_check_t += delta;

        if(device->isWindowActive())
        {
            driver->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));

            const irr::core::vector3df cam_pos = cam->getTarget();

            irr::core::stringw curr_loc = "Camera Location : \n";
            curr_loc += cam_pos.X;
            curr_loc += ", ";
            curr_loc += cam_pos.Y;
            curr_loc += ", ";
            curr_loc += cam_pos.Z;
            font->draw(curr_loc.c_str(), irr::core::rect<irr::s32>(10,10,260,22), irr::video::SColor(255, 255, 255, 255));
           
            this->smgr->drawAll();

            /*-- Check for serial port's existence every 5 seconds --*/
            if(port_check_t/5000) {
                if(!UConLink::checkPort(this->config.getSerialPort().c_str())) {
                    _logger->error("File to serial port vanished, cable yanked?");
                    delete link;
                    link = NULL;
                    
                    CEGUI::Window* guiRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
                    CEGUI::Window* guiSerialPortLabel = guiRoot->getChild("RigMotionContainer/SerialPortContainer/SerialPortLabel");

                    guiSerialPortLabel->setProperty("NormalTextColour", "FFDB1515");
                }
                port_check_t = 0;
            }

            if(this->gui_active) {
                CEGUI::System::getSingleton().renderAllGUIContexts();
                CEGUI::System::getSingleton().injectTimePulse(delta_t);
            } /*else {
                this->cursor->setVisible(true);
            }*/

            processMotionCommands(delta_t);


            /*move_y(rotational_shaft_node[0], linear_rail_node[0],
                   rotational_shaft_node[1], linear_rail_node[1],
                   2*M_PI, delta_t);

            move_x(rotational_shaft_node[2], linear_rail_node[2], 2*M_PI, delta_t);*/

            driver->endScene();
        }
        else
            device->yield();
    }
}

bool GUI::OnEvent(const irr::SEvent& event) {
    if(event.EventType == irr::EET_LOG_TEXT_EVENT) return true;
    else if(event.EventType == irr::EET_KEY_INPUT_EVENT) {
        if(event.KeyInput.Key == irr::EKEY_CODE::KEY_ESCAPE) {
            if(event.KeyInput.PressedDown) {
                if(!motionKeyState[0]) {
                    motionKeyState[0] = true;
                    this->gui_active = !this->gui_active;
                    
                    if(gui_active) {
                        this->startStaticAnimation();
                        this->cursor->setVisible(false);
                    }
                    else {
                        //this->cursor->setVisible(true);
                        //this->cursor->setActiveIcon(irr::gui::ECI_CROSS);
                        //this->cursor->setVisible(true);
                    }
                }
            } else {
                motionKeyState[0] = false;
            }
        } 
        else if(event.KeyInput.Key == irr::EKEY_CODE::KEY_HOME) {
            if(event.KeyInput.PressedDown) {
                if(!motionKeyState[1]) {
                    motionKeyState[1] = true;
                    motionMovementState[0] = true;                   
                }
            } else {
                motionKeyState[1] = false;
            }
        }
        else if(event.KeyInput.Key == irr::EKEY_CODE::KEY_END) {
            if(event.KeyInput.PressedDown) {
                if(!motionKeyState[2]) {
                    motionKeyState[2] = true;
                    motionMovementState[1] = true;                   
                }
            } else {
                motionKeyState[2] = false;
            }
        }
        else if(event.KeyInput.Key == irr::EKEY_CODE::KEY_DELETE) {
            if(event.KeyInput.PressedDown) {
                if(!motionKeyState[3]) {
                    motionKeyState[3] = true;
                    motionMovementState[2] = true;                   
                }
            } else {
                motionKeyState[3] = false;
            }
        }
        else if(event.KeyInput.Key == irr::EKEY_CODE::KEY_NEXT) {
            if(event.KeyInput.PressedDown) {
                if(!motionKeyState[4]) {
                    motionKeyState[4] = true;
                    motionMovementState[3] = true;                   
                }
            } else {
                motionKeyState[4] = false;
            }
        }
        else if(event.KeyInput.Key == irr::EKEY_CODE::KEY_INSERT) {
            if(event.KeyInput.PressedDown) {
                if(!motionKeyState[5]) {
                    motionKeyState[5] = true;
                    motionMovementState[4] = true;                   
                }
            } else {
                motionKeyState[5] = false;
            }
        }
        else if(event.KeyInput.Key == irr::EKEY_CODE::KEY_PRIOR) {
            if(event.KeyInput.PressedDown) {
                if(!motionKeyState[6]) {
                    motionKeyState[6] = true;
                    motionMovementState[5] = true;                   
                }
            } else {
                motionKeyState[6] = false;
            }
        }
        else if(event.KeyInput.Key == irr::EKEY_CODE::KEY_ADD || event.KeyInput.Key == irr::EKEY_CODE::KEY_PLUS) {
            this->cameraZoomIn(event.KeyInput.Shift);
        }
        else if(event.KeyInput.Key == irr::EKEY_CODE::KEY_MINUS || event.KeyInput.Key == irr::EKEY_CODE::KEY_SUBTRACT) {
            this->cameraZoomOut(event.KeyInput.Shift);
        }

        //_logger->warn("{0}", event.KeyInput.Key);

        if(this->gui_active) {
            this->guiRend->injectEvent(event);
        }
    }
    else if(event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
        if(this->gui_active) {
            this->guiRend->injectEvent(event);
            //this->guiRend->CEGUI::Renderer::endRendering
        } else {
            if(event.MouseInput.Event == irr::EMIE_MOUSE_WHEEL) {
                if(event.MouseInput.Wheel < 0) {
                    this->cameraZoomIn(event.MouseInput.Shift);                 
                } else {
                    this->cameraZoomOut(event.MouseInput.Shift);
                }
                _logger->warn("in wheel event");
            } else if(event.MouseInput.Event == irr::EMIE_MOUSE_MOVED) {

                if(event.MouseInput.isLeftPressed()) {
                    irr::core::position2df curr_pos = this->cursor->getRelativePosition();
                    this->cameraRotate(event.MouseInput.Shift, curr_pos);
                    //this->cursor->setPosition(irr::core::vector2df(0.5f, 0.5f));
                }

                _logger->warn("in move");
            }
        }
    }
    return true;
}

void GUI::initFrequencyLookup() {
    this->frequencyLookup[0] = 999.9610483646393;
	this->frequencyLookup[1] = 1074.4668543338776;
	this->frequencyLookup[2] = 1149.0657925605774;
	this->frequencyLookup[3] = 1223.5715985298157;
	this->frequencyLookup[4] = 1298.077404499054;
	this->frequencyLookup[5] = 1372.5832104682922;
	this->frequencyLookup[6] = 1447.0890164375305;
	this->frequencyLookup[7] = 1521.5948224067688;
	this->frequencyLookup[8] = 1596.100628376007;
	this->frequencyLookup[9] = 1670.6064343452454;
	this->frequencyLookup[10] = 1745.1122403144836;
	this->frequencyLookup[11] = 1819.618046283722;
	this->frequencyLookup[12] = 1894.1238522529602;
	this->frequencyLookup[13] = 1968.6296582221985;
	this->frequencyLookup[14] = 2043.1354641914368;
	this->frequencyLookup[15] = 2117.641270160675;
	this->frequencyLookup[16] = 2192.1470761299133;
	this->frequencyLookup[17] = 2266.6528820991516;
	this->frequencyLookup[18] = 2341.15868806839;
	this->frequencyLookup[19] = 2415.664494037628;
	this->frequencyLookup[20] = 2490.1703000068665;
	this->frequencyLookup[21] = 2564.6761059761047;
	this->frequencyLookup[22] = 2639.181911945343;
	this->frequencyLookup[23] = 2713.6877179145813;
	this->frequencyLookup[24] = 2788.1935238838196;
	this->frequencyLookup[25] = 2862.699329853058;
	this->frequencyLookup[26] = 2937.2982680797577;
	this->frequencyLookup[27] = 3011.804074048996;
	this->frequencyLookup[28] = 3086.3098800182343;
	this->frequencyLookup[29] = 3160.8156859874725;
	this->frequencyLookup[30] = 3235.321491956711;
	this->frequencyLookup[31] = 3309.827297925949;
	this->frequencyLookup[32] = 3384.3331038951874;
	this->frequencyLookup[33] = 3458.8389098644257;
	this->frequencyLookup[34] = 3533.344715833664;
	this->frequencyLookup[35] = 3607.850521802902;
	this->frequencyLookup[36] = 3682.3563277721405;
	this->frequencyLookup[37] = 3756.862133741379;
	this->frequencyLookup[38] = 3831.367939710617;
	this->frequencyLookup[39] = 3905.8737456798553;
	this->frequencyLookup[40] = 3980.3795516490936;
	this->frequencyLookup[41] = 4054.885357618332;
	this->frequencyLookup[42] = 4129.39116358757;
	this->frequencyLookup[43] = 4203.8969695568085;
	this->frequencyLookup[44] = 4278.402775526047;
	this->frequencyLookup[45] = 4352.908581495285;
	this->frequencyLookup[46] = 4427.414387464523;
	this->frequencyLookup[47] = 4501.920193433762;
	this->frequencyLookup[48] = 4576.425999403;
	this->frequencyLookup[49] = 4651.0249376297;
	this->frequencyLookup[50] = 4725.530743598938;
	this->frequencyLookup[51] = 4800.036549568176;
	this->frequencyLookup[52] = 4874.542355537415;
	this->frequencyLookup[53] = 4949.048161506653;
	this->frequencyLookup[54] = 5023.553967475891;
	this->frequencyLookup[55] = 5098.059773445129;
	this->frequencyLookup[56] = 5172.565579414368;
	this->frequencyLookup[57] = 5247.071385383606;
	this->frequencyLookup[58] = 5321.577191352844;
	this->frequencyLookup[59] = 5396.0829973220825;
	this->frequencyLookup[60] = 5470.588803291321;
	this->frequencyLookup[61] = 5545.094609260559;
	this->frequencyLookup[62] = 5619.600415229797;
	this->frequencyLookup[63] = 5694.106221199036;
	this->frequencyLookup[64] = 5768.612027168274;
	this->frequencyLookup[65] = 5843.117833137512;
	this->frequencyLookup[66] = 5917.6236391067505;
	this->frequencyLookup[67] = 5992.129445075989;
	this->frequencyLookup[68] = 6066.635251045227;
	this->frequencyLookup[69] = 6141.141057014465;
	this->frequencyLookup[70] = 6215.646862983704;
	this->frequencyLookup[71] = 6290.152668952942;
	this->frequencyLookup[72] = 6364.751607179642;
	this->frequencyLookup[73] = 6439.25741314888;
	this->frequencyLookup[74] = 6513.763219118118;
	this->frequencyLookup[75] = 6588.269025087357;
	this->frequencyLookup[76] = 6662.774831056595;
	this->frequencyLookup[77] = 6737.280637025833;
	this->frequencyLookup[78] = 6811.786442995071;
	this->frequencyLookup[79] = 6886.29224896431;
	this->frequencyLookup[80] = 6960.798054933548;
	this->frequencyLookup[81] = 7035.303860902786;
	this->frequencyLookup[82] = 7109.8096668720245;
	this->frequencyLookup[83] = 7184.315472841263;
	this->frequencyLookup[84] = 7258.821278810501;
	this->frequencyLookup[85] = 7333.327084779739;
	this->frequencyLookup[86] = 7407.832890748978;
	this->frequencyLookup[87] = 7482.338696718216;
	this->frequencyLookup[88] = 7556.844502687454;
	this->frequencyLookup[89] = 7631.3503086566925;
	this->frequencyLookup[90] = 7705.856114625931;
	this->frequencyLookup[91] = 7780.361920595169;
	this->frequencyLookup[92] = 7854.867726564407;
	this->frequencyLookup[93] = 7929.373532533646;
	this->frequencyLookup[94] = 8003.879338502884;
	this->frequencyLookup[95] = 8078.385144472122;
	this->frequencyLookup[96] = 8152.984082698822;
	this->frequencyLookup[97] = 8227.48988866806;
	this->frequencyLookup[98] = 8301.995694637299;
	this->frequencyLookup[99] = 8376.501500606537;
	this->frequencyLookup[100] = 8451.007306575775;
	this->frequencyLookup[101] = 8525.513112545013;
	this->frequencyLookup[102] = 8600.018918514252;
	this->frequencyLookup[103] = 8674.52472448349;
	this->frequencyLookup[104] = 8749.030530452728;
	this->frequencyLookup[105] = 8823.536336421967;
	this->frequencyLookup[106] = 8898.042142391205;
	this->frequencyLookup[107] = 8972.547948360443;
	this->frequencyLookup[108] = 9047.053754329681;
	this->frequencyLookup[109] = 9121.55956029892;
	this->frequencyLookup[110] = 9196.065366268158;
	this->frequencyLookup[111] = 9270.571172237396;
	this->frequencyLookup[112] = 9345.076978206635;
	this->frequencyLookup[113] = 9419.582784175873;
	this->frequencyLookup[114] = 9494.088590145111;
	this->frequencyLookup[115] = 9568.59439611435;
	this->frequencyLookup[116] = 9643.100202083588;
	this->frequencyLookup[117] = 9717.606008052826;
	this->frequencyLookup[118] = 9792.111814022064;
	this->frequencyLookup[119] = 9866.710752248764;
	this->frequencyLookup[120] = 9941.216558218002;
	this->frequencyLookup[121] = 10015.72236418724;
	this->frequencyLookup[122] = 10090.228170156479;
	this->frequencyLookup[123] = 10164.733976125717;
	this->frequencyLookup[124] = 10239.239782094955;
	this->frequencyLookup[125] = 10313.745588064194;
	this->frequencyLookup[126] = 10388.251394033432;
	this->frequencyLookup[127] = 10462.75720000267;
	this->frequencyLookup[128] = 10537.263005971909;
	this->frequencyLookup[129] = 10611.768811941147;
	this->frequencyLookup[130] = 10686.274617910385;
	this->frequencyLookup[131] = 10760.780423879623;
	this->frequencyLookup[132] = 10835.286229848862;
	this->frequencyLookup[133] = 10909.7920358181;
	this->frequencyLookup[134] = 10984.297841787338;
	this->frequencyLookup[135] = 11058.803647756577;
	this->frequencyLookup[136] = 11133.309453725815;
	this->frequencyLookup[137] = 11207.815259695053;
	this->frequencyLookup[138] = 11282.321065664291;
	this->frequencyLookup[139] = 11356.82687163353;
	this->frequencyLookup[140] = 11431.332677602768;
	this->frequencyLookup[141] = 11505.838483572006;
	this->frequencyLookup[142] = 11580.437421798706;
	this->frequencyLookup[143] = 11654.943227767944;
	this->frequencyLookup[144] = 11729.449033737183;
	this->frequencyLookup[145] = 11803.95483970642;
	this->frequencyLookup[146] = 11878.46064567566;
	this->frequencyLookup[147] = 11952.966451644897;
	this->frequencyLookup[148] = 12027.472257614136;
	this->frequencyLookup[149] = 12101.978063583374;
	this->frequencyLookup[150] = 12176.483869552612;
	this->frequencyLookup[151] = 12250.98967552185;
	this->frequencyLookup[152] = 12325.495481491089;
	this->frequencyLookup[153] = 12400.001287460327;
	this->frequencyLookup[154] = 12474.507093429565;
	this->frequencyLookup[155] = 12549.012899398804;
	this->frequencyLookup[156] = 12623.518705368042;
	this->frequencyLookup[157] = 12698.02451133728;
	this->frequencyLookup[158] = 12772.530317306519;
	this->frequencyLookup[159] = 12847.036123275757;
	this->frequencyLookup[160] = 12921.541929244995;
	this->frequencyLookup[161] = 12996.047735214233;
	this->frequencyLookup[162] = 13070.553541183472;
	this->frequencyLookup[163] = 13145.05934715271;
	this->frequencyLookup[164] = 13219.565153121948;
	this->frequencyLookup[165] = 13294.164091348648;
	this->frequencyLookup[166] = 13368.669897317886;
	this->frequencyLookup[167] = 13443.175703287125;
	this->frequencyLookup[168] = 13517.681509256363;
	this->frequencyLookup[169] = 13592.187315225601;
	this->frequencyLookup[170] = 13666.69312119484;
	this->frequencyLookup[171] = 13741.198927164078;
	this->frequencyLookup[172] = 13815.704733133316;
	this->frequencyLookup[173] = 13890.210539102554;
	this->frequencyLookup[174] = 13964.716345071793;
	this->frequencyLookup[175] = 14039.22215104103;
	this->frequencyLookup[176] = 14113.72795701027;
	this->frequencyLookup[177] = 14188.233762979507;
	this->frequencyLookup[178] = 14262.739568948746;
	this->frequencyLookup[179] = 14337.245374917984;
	this->frequencyLookup[180] = 14411.751180887222;
	this->frequencyLookup[181] = 14486.25698685646;
	this->frequencyLookup[182] = 14560.762792825699;
	this->frequencyLookup[183] = 14635.268598794937;
	this->frequencyLookup[184] = 14709.774404764175;
	this->frequencyLookup[185] = 14784.280210733414;
	this->frequencyLookup[186] = 14858.786016702652;
	this->frequencyLookup[187] = 14933.29182267189;
	this->frequencyLookup[188] = 15007.797628641129;
	this->frequencyLookup[189] = 15082.396566867828;
	this->frequencyLookup[190] = 15156.902372837067;
	this->frequencyLookup[191] = 15231.408178806305;
	this->frequencyLookup[192] = 15305.913984775543;
	this->frequencyLookup[193] = 15380.419790744781;
	this->frequencyLookup[194] = 15454.92559671402;
	this->frequencyLookup[195] = 15529.431402683258;
	this->frequencyLookup[196] = 15603.937208652496;
	this->frequencyLookup[197] = 15678.443014621735;
	this->frequencyLookup[198] = 15752.948820590973;
	this->frequencyLookup[199] = 15827.454626560211;
	this->frequencyLookup[200] = 15901.96043252945;
	this->frequencyLookup[201] = 15976.466238498688;
	this->frequencyLookup[202] = 16050.972044467926;
	this->frequencyLookup[203] = 16125.477850437164;
	this->frequencyLookup[204] = 16199.983656406403;
	this->frequencyLookup[205] = 16274.48946237564;
	this->frequencyLookup[206] = 16348.99526834488;
	this->frequencyLookup[207] = 16423.501074314117;
	this->frequencyLookup[208] = 16498.006880283356;
	this->frequencyLookup[209] = 16572.512686252594;
	this->frequencyLookup[210] = 16647.018492221832;
	this->frequencyLookup[211] = 16721.52429819107;
	this->frequencyLookup[212] = 16796.12323641777;
	this->frequencyLookup[213] = 16870.62904238701;
	this->frequencyLookup[214] = 16945.134848356247;
	this->frequencyLookup[215] = 17019.640654325485;
	this->frequencyLookup[216] = 17094.146460294724;
	this->frequencyLookup[217] = 17168.65226626396;
	this->frequencyLookup[218] = 17243.1580722332;
	this->frequencyLookup[219] = 17317.66387820244;
	this->frequencyLookup[220] = 17392.169684171677;
	this->frequencyLookup[221] = 17466.675490140915;
	this->frequencyLookup[222] = 17541.181296110153;
	this->frequencyLookup[223] = 17615.68710207939;
	this->frequencyLookup[224] = 17690.19290804863;
	this->frequencyLookup[225] = 17764.698714017868;
	this->frequencyLookup[226] = 17839.204519987106;
	this->frequencyLookup[227] = 17913.710325956345;
	this->frequencyLookup[228] = 17988.216131925583;
	this->frequencyLookup[229] = 18062.72193789482;
	this->frequencyLookup[230] = 18137.22774386406;
	this->frequencyLookup[231] = 18211.733549833298;
	this->frequencyLookup[232] = 18286.239355802536;
	this->frequencyLookup[233] = 18360.745161771774;
	this->frequencyLookup[234] = 18435.250967741013;
	this->frequencyLookup[235] = 18509.849905967712;
	this->frequencyLookup[236] = 18584.35571193695;
	this->frequencyLookup[237] = 18658.86151790619;
	this->frequencyLookup[238] = 18733.367323875427;
	this->frequencyLookup[239] = 18807.873129844666;
	this->frequencyLookup[240] = 18882.378935813904;
	this->frequencyLookup[241] = 18956.884741783142;
	this->frequencyLookup[242] = 19031.39054775238;
	this->frequencyLookup[243] = 19105.89635372162;
	this->frequencyLookup[244] = 19180.402159690857;
	this->frequencyLookup[245] = 19254.907965660095;
	this->frequencyLookup[246] = 19329.413771629333;
	this->frequencyLookup[247] = 19403.91957759857;
	this->frequencyLookup[248] = 19478.42538356781;
	this->frequencyLookup[249] = 19552.93118953705;
	this->frequencyLookup[250] = 19627.436995506287;
	this->frequencyLookup[251] = 19701.942801475525;
	this->frequencyLookup[252] = 19776.448607444763;
	this->frequencyLookup[253] = 19850.954413414;
	this->frequencyLookup[254] = 19925.46021938324;
	this->frequencyLookup[255] = 19999.966025352478;
}

void GUI::processMotionCommands(float delta_t) {
    if(motionMovementState[4]) {
        
    }
}

void GUI::move_x(irr::scene::ISceneNode* rotary_node_x, irr::scene::ISceneNode* linear_node_x,
            float rotary_speed, float delta_t) {
    float delta_rot = rotary_speed * delta_t * 180.0/M_PI;
    irr::core::vector3df curr = rotary_node_x->getRotation();
    curr += irr::core::vector3df(0, delta_rot, 0);
    
    this->rotational_shaft_node[2]->setRotation(curr);

    //Lead length for 1000mm class is 10mm;
    float delta_pos = delta_rot * 10.0/360;
    curr = linear_rail_node[2]->getPosition();
    curr += irr::core::vector3df(0, delta_pos, 0);
    linear_node_x->setPosition(curr);
} 

void GUI::move_y(irr::scene::ISceneNode* rotary_node_y_l, irr::scene::ISceneNode* linear_node_y_l,
            irr::scene::ISceneNode* rotary_node_y_r, irr::scene::ISceneNode* linear_node_y_r,
            float rotary_speed, float delta_t) {
    float delta_rot = rotary_speed * delta_t * 180.0/M_PI;
    rotary_node_y_l->setRotation(rotary_node_y_l->getRotation() + irr::core::vector3df(0, delta_rot, 0));
    rotary_node_y_r->setRotation(rotary_node_y_r->getRotation() + irr::core::vector3df(0, delta_rot, 0));

    //Lead length for 1000mm class is 10mm;
    float delta_pos = delta_rot * 10.0/360;
    linear_node_y_l->setPosition(linear_node_y_l->getPosition() + irr::core::vector3df(0, delta_pos, 0));
    linear_node_y_r->setPosition(linear_node_y_r->getPosition() + irr::core::vector3df(0, delta_pos, 0));
} 

void GUI::addShaders() {
    _logger->trace("Adding shader programs...");
    irr::io::path toon_black_metalv = "data/shaders/toon_black_metal.vert";
    irr::io::path toon_black_metalf = "data/shaders/toon_black_metal.frag";

    irr::io::path toon_silver_metalv = "data/shaders/toon_silver_metal.vert";
    irr::io::path toon_silver_metalf = "data/shaders/toon_silver_metal.frag";
    
    irr::io::path toon_gold_metalv = "data/shaders/toon_gold_metal.vert";
    irr::io::path toon_gold_metalf = "data/shaders/toon_gold_metal.frag";
    
    irr::io::path toon_blue_metalv = "data/shaders/toon_blue_metal.vert";
    irr::io::path toon_blue_metalf = "data/shaders/toon_blue_metal.frag";
    
    irr::io::path toon_green_metalv = "data/shaders/toon_green_metal.vert";
    irr::io::path toon_green_metalf = "data/shaders/toon_green_metal.frag";

    irr::video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();
    this->toon_black_metal_shader = gpu->addHighLevelShaderMaterialFromFiles(toon_black_metalv, "main",
                                                                                irr::video::EVST_VS_1_1,
                                                                                toon_black_metalf, "main", 
                                                                                irr::video::EPST_PS_1_1);
    this->toon_silver_metal_shader = gpu->addHighLevelShaderMaterialFromFiles(toon_silver_metalv, "main", 
                                                                                irr::video::EVST_VS_1_1,
                                                                                toon_silver_metalf, "main", 
                                                                                irr::video::EPST_PS_1_1);
    this->toon_gold_metal_shader = gpu->addHighLevelShaderMaterialFromFiles(toon_gold_metalv, "main", 
                                                                                irr::video::EVST_VS_1_1,
                                                                                toon_gold_metalf, "main", 
                                                                                irr::video::EPST_PS_1_1);
    this->toon_blue_metal_shader = gpu->addHighLevelShaderMaterialFromFiles(toon_blue_metalv, "main",
                                                                                 irr::video::EVST_VS_1_1,
                                                                                toon_blue_metalf, "main", 
                                                                                irr::video::EPST_PS_1_1);
    this->toon_green_metal_shader = gpu->addHighLevelShaderMaterialFromFiles(toon_green_metalv, "main", 
                                                                                irr::video::EVST_VS_1_1,
                                                                                toon_green_metalf, "main", 
                                                                                irr::video::EPST_PS_1_1);
}

void GUI::addLightsandCameras() {
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
    
    this->cam = this->smgr->addCameraSceneNodeFPS(smgr->getRootSceneNode(),
                                                  5.f, .5f, 0, keyMap, 8,
                                                  false, 0.f, false, true);*/
    _logger->trace("Adding camera and light node...");
    this->cam = this->smgr->addCameraSceneNode(this->smgr->getRootSceneNode());
    this->light = this->smgr->addLightSceneNode(); 
    this->light->setID(static_cast<irr::s32>(0));
    this->light->setLightType(irr::video::ELT_DIRECTIONAL);
    this->light->setPosition(irr::core::vector3df(0., 0., 1.));

    irr::scene::ISceneNode* pLight = this->smgr->addEmptySceneNode(0, 0);
    this->light->setParent(pLight);
    irr::core::vector3df curr_rot = pLight->getRotation();
    curr_rot += irr::core::vector3df(0.0, 45.0, 45.0);
    pLight->setRotation(curr_rot);
    //this->cam->setRotation(irr::core::vector3df(0, 180.0, 0));
    //
    this->smgr->addLightSceneNode(0, irr::core::vector3df(0, 0, 100));
    
    this->cam->setPosition(irr::core::vector3df(-1000, 1000.0, 500.f));
    this->cam->setTarget(irr::core::vector3df(0, 600.f, 0.f));

    /*irr::core::matrix4 F = cam->getProjectionMatrix();
    _logger->trace("Projection Matrix :");
    _logger->trace("{0}, {1}, {2}, {3}", F[0], F[1], F[2], F[3]);
    _logger->trace("{0}, {1}, {2}, {3}", F[4], F[5], F[6], F[7]);
    _logger->trace("{0}, {1}, {2}, {3}", F[8], F[9], F[10], F[11]);
    _logger->trace("{0}, {1}, {2}, {3}", F[12], F[13], F[14], F[15]);

    irr::core::matrix4 F2;
    F2.buildProjectionMatrixOrthoLH(800, 600, 10, 10000);
    cam->setProjectionMatrix(F2);*/
}

void GUI::addMeshes() {
    _logger->trace("Adding meshes...");

    this->start_shaft_holder = this->smgr->getMesh("data/meshis/start_shaft_holder.stl");
    this->finish_shaft_holder = this->smgr->getMesh("data/meshis/finish_shaft_holder.stl");
    this->motor_shaft_link = this->smgr->getMesh("data/meshis/motor_shaft_link.stl");
    this->motor = this->smgr->getMesh("data/meshis/motor.stl");
    this->steel_rail = this->smgr->getMesh("data/meshis/steel_rail.stl");
    this->aluminium_back = this->smgr->getMesh("data/meshis/aluminium_back.stl");
    this->finish_bearing = this->smgr->getMesh("data/meshis/finish_bearing.stl");
    this->start_bearing = this->smgr->getMesh("data/meshis/start_bearing.stl");

    this->rail_top = this->smgr->getMesh("data/meshis/rail_top.stl");
    this->rail_ball_screw = this->smgr->getMesh("data/meshis/rail_ball_screw.stl");
    this->rail_clamp = this->smgr->getMesh("data/meshis/rail_clamp.stl");

    this->shaft = this->smgr->getMesh("data/meshis/shaft.ply");
    this->coupling = this->smgr->getMesh("data/meshis/coupling.ply");

    irr::scene::IMesh* ground = this->smgr->getGeometryCreator()->createPlaneMesh(irr::core::dimension2d<irr::f32>(256.0, 256.0),
                                                                            irr::core::dimension2d<irr::u32>(100, 100),
                                                                            0,
                                                                            irr::core::dimension2df(100., 100.));
    irr::video::ITexture* wooden = this->driver->getTexture("data/texture/dry_cracked_boards.png");
    irr::scene::ISceneNode* ground_node = this->smgr->addMeshSceneNode(ground);
    ground_node->setMaterialTexture(0, wooden);
    ground_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
   
}

void GUI::createFrame() {

    for(int i = 0; i < 3; i++) {
		this->linear_guide_node[i] = smgr->addEmptySceneNode(0, 3*i+1);
		this->linear_rail_node[i] = smgr->addEmptySceneNode(0, 3*i+2);
		this->rotational_shaft_node[i] = smgr->addEmptySceneNode(0, 3*i+3);

		this->start_shaft_holder_node[i] = smgr->addAnimatedMeshSceneNode(this->start_shaft_holder);
		this->finish_shaft_holder_node[i] = smgr->addAnimatedMeshSceneNode(this->finish_shaft_holder);
		this->motor_shaft_link_node[i] = smgr->addAnimatedMeshSceneNode(this->motor_shaft_link);
		this->motor_node[i] = smgr->addAnimatedMeshSceneNode(this->motor);
		this->steel_rail_node[i] = smgr->addAnimatedMeshSceneNode(this->steel_rail);
		this->aluminium_back_node[i] = smgr->addAnimatedMeshSceneNode(this->aluminium_back);
		this->finish_bearing_node[i] = smgr->addAnimatedMeshSceneNode(this->finish_bearing);
		this->start_bearing_node[i] = smgr->addAnimatedMeshSceneNode(this->start_bearing);
		
        this->rail_top_node[i] = smgr->addAnimatedMeshSceneNode(this->rail_top);
		this->rail_ball_screw_node[i] = smgr->addAnimatedMeshSceneNode(this->rail_ball_screw);
		this->rail_clamp_node[i] = smgr->addAnimatedMeshSceneNode(this->rail_clamp);

		this->shaft_node[i] = smgr->addAnimatedMeshSceneNode(this->shaft);
		this->coupling_node[i] = smgr->addAnimatedMeshSceneNode(this->coupling);

        this->linear_guide_node[i]->setPosition(LEFT_OFFSET);
		this->linear_guide_node[i]->addChild(this->start_shaft_holder_node[i]);
        this->start_shaft_holder_node[i]->setPosition(-LEFT_OFFSET);
		this->linear_guide_node[i]->addChild(this->finish_shaft_holder_node[i]);
        this->finish_shaft_holder_node[i]->setPosition(-LEFT_OFFSET);
		this->linear_guide_node[i]->addChild(this->motor_shaft_link_node[i]);
        this->motor_shaft_link_node[i]->setPosition(-LEFT_OFFSET);
		this->linear_guide_node[i]->addChild(this->motor_node[i]);
        this->motor_node[i]->setPosition(-LEFT_OFFSET);
		this->linear_guide_node[i]->addChild(this->steel_rail_node[i]);
        this->steel_rail_node[i]->setPosition(-LEFT_OFFSET);
		this->linear_guide_node[i]->addChild(this->aluminium_back_node[i]);
        this->aluminium_back_node[i]->setPosition(-LEFT_OFFSET);
		this->linear_guide_node[i]->addChild(this->finish_bearing_node[i]);
        this->finish_bearing_node[i]->setPosition(-LEFT_OFFSET);
		this->linear_guide_node[i]->addChild(this->start_bearing_node[i]);
        this->start_bearing_node[i]->setPosition(-LEFT_OFFSET);
		
        this->rotational_shaft_node[i]->setPosition(COUPLING_OFFSET);
		this->rotational_shaft_node[i]->addChild(this->coupling_node[i]);
		this->rotational_shaft_node[i]->addChild(this->shaft_node[i]);
		this->coupling_node[i]->setPosition(IRR_ORIGIN);
		this->shaft_node[i]->setPosition(IRR_ORIGIN + SHAFT_Y_OFFEST);

		this->linear_rail_node[i]->setPosition(RAIL_OFFSET);
		this->rail_top_node[i]->setParent(this->linear_rail_node[i]);
		this->rail_top_node[i]->setPosition(-RAIL_OFFSET);
		this->rail_ball_screw_node[i]->setParent(this->linear_rail_node[i]);
		this->rail_ball_screw_node[i]->setPosition(-RAIL_OFFSET);
		this->rail_clamp_node[i]->setParent(this->linear_rail_node[i]);
		this->rail_clamp_node[i]->setPosition(-RAIL_OFFSET);
		this->linear_rail_node[i]->setPosition(IRR_ORIGIN);

		this->linear_guide_node[i]->addChild(this->linear_rail_node[i]);
        this->linear_rail_node[i]->setPosition(-LEFT_OFFSET);
		this->linear_guide_node[i]->addChild(this->rotational_shaft_node[i]);
        this->rotational_shaft_node[i]->setPosition(IRR_ORIGIN);

		this->start_shaft_holder_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_black_metal_shader);
		this->finish_shaft_holder_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_black_metal_shader);
		this->motor_shaft_link_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_black_metal_shader);
		this->motor_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_blue_metal_shader);
		this->steel_rail_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_gold_metal_shader);
		this->aluminium_back_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_silver_metal_shader);
		this->finish_bearing_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_silver_metal_shader);
		this->start_bearing_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_silver_metal_shader);
		
        this->rail_top_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_black_metal_shader);
		this->rail_ball_screw_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_silver_metal_shader);
		this->rail_clamp_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_silver_metal_shader);

		this->shaft_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_green_metal_shader);
		this->coupling_node[i]->setMaterialType((irr::video::E_MATERIAL_TYPE)this->toon_blue_metal_shader);
    }

    this->linear_guide_node[1]->setPosition(this->linear_guide_node[1]->getPosition() + RIGHT_OFFSET);
    this->linear_guide_node[1]->setRotation(this->linear_guide_node[1]->getRotation() + RIGHT_ROTATION);

    this->linear_guide_node[2]->setRotation(this->linear_guide_node[2]->getRotation() + HORIZ_ROTATION);
    this->linear_guide_node[2]->setPosition(this->linear_guide_node[2]->getPosition() + HORIZ_OFFSET);
    this->linear_guide_node[2]->setParent(this->linear_rail_node[0]);    

}

void GUI::cameraZoomIn(bool rapid) {
    irr::core::vector3df a = this->cam->getPosition();
    irr::core::vector3df b = this->cam->getTarget();

    irr::core::vector3df cam_plane = (b-a).normalize();

    if(rapid) {
        this->cam->setPosition(a + cam_plane * this->cam_zoom_speed * this->shift_multiplier);
        this->cam->setTarget(a + cam_plane * this->cam_zoom_speed * 2 * this->shift_multiplier);
    } else {
        this->cam->setPosition(a + cam_plane * cam_zoom_speed);
        this->cam->setTarget(a + cam_plane * cam_zoom_speed * 2);
    }
}

void GUI::cameraZoomOut(bool rapid) {
    irr::core::vector3df a = this->cam->getPosition();
    irr::core::vector3df b = this->cam->getTarget();

    irr::core::vector3df cam_plane = (b-a).normalize();

    if(rapid) {
        this->cam->setPosition(a - cam_plane * this->cam_zoom_speed * this->shift_multiplier);
        this->cam->setTarget(a + cam_plane * this->cam_zoom_speed * this->shift_multiplier);
    } else {
        this->cam->setPosition(a - cam_plane * cam_zoom_speed);
        this->cam->setTarget(a + cam_plane * cam_zoom_speed);
    }
}

void GUI::cameraRotate(bool rapid, irr::core::position2df mousePos) {
}

void GUI::bootstrapCEGUI() {
    
    _logger->trace("Bootstrapping the GUI system...");
    this->guiRend = &(CEGUI::IrrlichtRenderer::bootstrapSystem(*(this->device)));

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

    _logger->trace("Adding the awesome mouse cursor...");
    CEGUI::Image* guiMouseCursor = &(CEGUI::ImageManager::getSingleton().get("GameMenuImages/MouseCursor"));
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage(guiMouseCursor);

    setupStaticAnimation();
    startStaticAnimation();
    setupDynamicAnimation();
    setupDynamicEvents();
    loadDatafromSettings();
}

void GUI::setupStaticAnimation() {

    _logger->trace("Setting up Static Animation...");
    CEGUI::WindowManager& guiWmgr = CEGUI::WindowManager::getSingleton();
    
    CEGUI::Window* guiRoot = guiWmgr.loadLayoutFromFile("GameMenu.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(guiRoot);
    
    CEGUI::AnimationManager& guiAnimgr = CEGUI::AnimationManager::getSingleton();
    guiAnimgr.loadAnimationsFromXML("GameMenu.anims");

    CEGUI::AnimationInstance* guiTopBarAnimInst = guiAnimgr.instantiateAnimation("TopBarMoveInAnimation");
    CEGUI::Window* guiTopBarWin = guiRoot->getChild("TopBar"); 
    guiTopBarAnimInst->setTargetWindow(guiTopBarWin);
    this->guiStaticAnimInst.push_back(guiTopBarAnimInst);

    CEGUI::AnimationInstance* guiBotBarAnimInst = guiAnimgr.instantiateAnimation("BotBarMoveInAnimation");
    CEGUI::Window* guiBotBarWin = guiRoot->getChild("BotBar"); 
    guiBotBarAnimInst->setTargetWindow(guiBotBarWin);
    this->guiStaticAnimInst.push_back(guiBotBarAnimInst);
    
    CEGUI::AnimationInstance* guiStartQuitContainerAnimInst = guiAnimgr.instantiateAnimation("StartQuitContainerZoomInAnimation");
    CEGUI::Window* guiStartQuitContainerWin = guiRoot->getChild("StartQuitContainer"); 
    guiStartQuitContainerAnimInst->setTargetWindow(guiStartQuitContainerWin);
    this->guiStaticAnimInst.push_back(guiStartQuitContainerAnimInst);
    
    CEGUI::AnimationInstance* guiCamDataContainerAnimInst = guiAnimgr.instantiateAnimation("CamDataContainerMoveInAnimation");
    CEGUI::Window* guiCamDataContainerWin = guiRoot->getChild("CamDataContainer"); 
    guiCamDataContainerAnimInst->setTargetWindow(guiCamDataContainerWin);
    this->guiStaticAnimInst.push_back(guiCamDataContainerAnimInst);
    
    CEGUI::AnimationInstance* guiRigMotionContainerAnimInst = guiAnimgr.instantiateAnimation("RigMotionContainerMoveInAnimation");
    CEGUI::Window* guiRigMotionContainerWin = guiRoot->getChild("RigMotionContainer"); 
    guiRigMotionContainerAnimInst->setTargetWindow(guiRigMotionContainerWin);
    this->guiStaticAnimInst.push_back(guiRigMotionContainerAnimInst);
}

void GUI::startStaticAnimation() {
    
    std::vector<CEGUI::AnimationInstance *>::iterator it = this->guiStaticAnimInst.begin();
    while(it != this->guiStaticAnimInst.end()) {
        (*it)->setPosition((*it)->getDefinition()->getDuration());
        (*it)->apply();
        (*it)->start();
        it++;
    }

}

void GUI::setupDynamicAnimation() {

    CEGUI::AnimationManager& guiAnimgr = CEGUI::AnimationManager::getSingleton();
    CEGUI::Window* guiRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

    CEGUI::AnimationInstance* guiRefreshPortOverAnimInst = guiAnimgr.instantiateAnimation("RefreshPortMouseOverAnimation");
    CEGUI::Window* guiRefreshPortWin = guiRoot->getChild("RigMotionContainer/SerialPortContainer/Refresh");
    guiRefreshPortOverAnimInst->setTargetWindow(guiRefreshPortWin);
    this->guiDynamicAnimInst.insert(std::pair<std::string, CEGUI::AnimationInstance *>("RefreshPortOver", guiRefreshPortOverAnimInst));

    CEGUI::AnimationInstance* guiRefreshPortClickAnimInst = guiAnimgr.instantiateAnimation("RefreshPortMouseClickAnimation");
    guiRefreshPortClickAnimInst->setTargetWindow(guiRefreshPortWin);
    this->guiDynamicAnimInst.insert(std::pair<std::string, CEGUI::AnimationInstance *>("RefreshPortClick", guiRefreshPortClickAnimInst));

    CEGUI::AnimationInstance* guiResetMotionOverAnimInst = guiAnimgr.instantiateAnimation("ButtonMouseOverAnimation");
    CEGUI::Window* guiResetMotionEditboxWin = guiRoot->getChild("RigMotionContainer/ResetContainer/ResetEditbox");
    guiResetMotionOverAnimInst->setTargetWindow(guiResetMotionEditboxWin);
    this->guiDynamicAnimInst.insert(std::pair<std::string, CEGUI::AnimationInstance *>("ResetMotionOver", guiResetMotionOverAnimInst));
    
    CEGUI::AnimationInstance* guiResetMotionClickAnimInst = guiAnimgr.instantiateAnimation("ButtonMouseClickAnimation");
    CEGUI::Window* guiResetMotionWin = guiRoot->getChild("RigMotionContainer/ResetContainer/ResetLabel");
    guiResetMotionClickAnimInst->setTargetWindow(guiResetMotionWin);
    this->guiDynamicAnimInst.insert(std::pair<std::string, CEGUI::AnimationInstance *>("ResetMotionClick", guiResetMotionClickAnimInst));

    CEGUI::AnimationInstance* guiStartAppOverAnimInst = guiAnimgr.instantiateAnimation("ButtonMouseOverAnimation");
    CEGUI::Window* guiStartAppEditboxWin = guiRoot->getChild("StartQuitContainer/StartEditbox");
    guiStartAppOverAnimInst->setTargetWindow(guiStartAppEditboxWin);
    this->guiDynamicAnimInst.insert(std::pair<std::string, CEGUI::AnimationInstance *>("StartAppOver", guiStartAppOverAnimInst));
    
    CEGUI::AnimationInstance* guiStartAppClickAnimInst = guiAnimgr.instantiateAnimation("ButtonMouseClickAnimation");
    CEGUI::Window* guiStartAppWin = guiRoot->getChild("StartQuitContainer/StartLabel");
    guiStartAppClickAnimInst->setTargetWindow(guiStartAppWin);
    this->guiDynamicAnimInst.insert(std::pair<std::string, CEGUI::AnimationInstance *>("StartAppClick", guiStartAppClickAnimInst));
    guiStartAppClickAnimInst->getEventReceiver()->subscribeEvent(CEGUI::AnimationInstance::EventAnimationStopped, CEGUI::SubscriberSlot(&GUI::handleStart, this));
    
    CEGUI::AnimationInstance* guiQuitAppOverAnimInst = guiAnimgr.instantiateAnimation("ButtonMouseOverAnimation");
    CEGUI::Window* guiQuitAppEditboxWin = guiRoot->getChild("StartQuitContainer/QuitEditbox");
    guiQuitAppOverAnimInst->setTargetWindow(guiQuitAppEditboxWin);
    this->guiDynamicAnimInst.insert(std::pair<std::string, CEGUI::AnimationInstance *>("QuitAppOver", guiQuitAppOverAnimInst));
    
    CEGUI::AnimationInstance* guiQuitAppClickAnimInst = guiAnimgr.instantiateAnimation("ButtonMouseClickAnimation");
    CEGUI::Window* guiQuitAppWin = guiRoot->getChild("StartQuitContainer/QuitLabel");
    guiQuitAppClickAnimInst->setTargetWindow(guiQuitAppWin);
    this->guiDynamicAnimInst.insert(std::pair<std::string, CEGUI::AnimationInstance *>("QuitAppClick", guiQuitAppClickAnimInst));
    guiQuitAppClickAnimInst->getEventReceiver()->subscribeEvent(CEGUI::AnimationInstance::EventAnimationStopped, CEGUI::SubscriberSlot(&GUI::handleQuit, this));

}

void GUI::setupDynamicEvents() {
    
    CEGUI::Window* guiRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    
    CEGUI::Window* guiRefreshPortWin = guiRoot->getChild("RigMotionContainer/SerialPortContainer/Refresh");
    guiRefreshPortWin->subscribeEvent(CEGUI::Window::EventMouseEntersArea, CEGUI::SubscriberSlot(&GUI::handleRefreshPortLoopStart, this));
    guiRefreshPortWin->subscribeEvent(CEGUI::Window::EventMouseLeavesArea, CEGUI::SubscriberSlot(&GUI::handleRefreshPortLoopStop, this));
    guiRefreshPortWin->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::SubscriberSlot(&GUI::handleRefreshPortClick, this));

    CEGUI::Window* guiSerialPortEditboxWin = guiRoot->getChild("RigMotionContainer/SerialPortContainer/SerialPortEditbox");
    guiSerialPortEditboxWin->subscribeEvent(CEGUI::Window::EventDeactivated, CEGUI::SubscriberSlot(&GUI::handleSerialPortEditboxDeactive, this));

    CEGUI::Window* guiSpeedXEditboxWin = guiRoot->getChild("RigMotionContainer/SpeedXContainer/SpeedXEditbox");
    guiSpeedXEditboxWin->subscribeEvent(CEGUI::Window::EventDeactivated, CEGUI::SubscriberSlot(&GUI::handleFloatingEditboxDeactive, this));
    guiSpeedXEditboxWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyKeyDown, this));
    guiSpeedXEditboxWin->subscribeEvent(CEGUI::Window::EventCharacterKey, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyCharacterKey, this));
    
    CEGUI::Window* guiSpeedYEditboxWin = guiRoot->getChild("RigMotionContainer/SpeedYContainer/SpeedYEditbox");
    guiSpeedYEditboxWin->subscribeEvent(CEGUI::Window::EventDeactivated, CEGUI::SubscriberSlot(&GUI::handleFloatingEditboxDeactive, this));
    guiSpeedYEditboxWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyKeyDown, this));
    guiSpeedYEditboxWin->subscribeEvent(CEGUI::Window::EventCharacterKey, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyCharacterKey, this));
    
    CEGUI::Window* guiSpeedZEditboxWin = guiRoot->getChild("RigMotionContainer/SpeedZContainer/SpeedZEditbox");
    guiSpeedZEditboxWin->subscribeEvent(CEGUI::Window::EventDeactivated, CEGUI::SubscriberSlot(&GUI::handleFloatingEditboxDeactive, this));
    guiSpeedZEditboxWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyKeyDown, this));
    guiSpeedZEditboxWin->subscribeEvent(CEGUI::Window::EventCharacterKey, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyCharacterKey, this));
    
    CEGUI::Window* guiLengthXEditboxWin = guiRoot->getChild("RigMotionContainer/LengthXContainer/LengthXEditbox");
    guiLengthXEditboxWin->subscribeEvent(CEGUI::Window::EventDeactivated, CEGUI::SubscriberSlot(&GUI::handleFloatingEditboxDeactive, this));
    guiLengthXEditboxWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyKeyDown, this));
    guiLengthXEditboxWin->subscribeEvent(CEGUI::Window::EventCharacterKey, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyCharacterKey, this));
    
    CEGUI::Window* guiLengthYEditboxWin = guiRoot->getChild("RigMotionContainer/LengthYContainer/LengthYEditbox");
    guiLengthYEditboxWin->subscribeEvent(CEGUI::Window::EventDeactivated, CEGUI::SubscriberSlot(&GUI::handleFloatingEditboxDeactive, this));
    guiLengthYEditboxWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyKeyDown, this));
    guiLengthYEditboxWin->subscribeEvent(CEGUI::Window::EventCharacterKey, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyCharacterKey, this));
    
    CEGUI::Window* guiLengthZEditboxWin = guiRoot->getChild("RigMotionContainer/LengthZContainer/LengthZEditbox");
    guiLengthZEditboxWin->subscribeEvent(CEGUI::Window::EventDeactivated, CEGUI::SubscriberSlot(&GUI::handleFloatingEditboxDeactive, this));
    guiLengthZEditboxWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyKeyDown, this));
    guiLengthZEditboxWin->subscribeEvent(CEGUI::Window::EventCharacterKey, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyCharacterKey, this));
    
    CEGUI::Window* guiGridXEditboxWin = guiRoot->getChild("RigMotionContainer/GridXContainer/GridXEditbox");
    guiGridXEditboxWin->subscribeEvent(CEGUI::Window::EventDeactivated, CEGUI::SubscriberSlot(&GUI::handleIntegerEditboxDeactive, this));
    guiGridXEditboxWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyKeyDown, this));
    guiGridXEditboxWin->subscribeEvent(CEGUI::Window::EventCharacterKey, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyCharacterKey, this));
    
    CEGUI::Window* guiGridYEditboxWin = guiRoot->getChild("RigMotionContainer/GridYContainer/GridYEditbox");
    guiGridYEditboxWin->subscribeEvent(CEGUI::Window::EventDeactivated, CEGUI::SubscriberSlot(&GUI::handleIntegerEditboxDeactive, this));
    guiGridYEditboxWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyKeyDown, this));
    guiGridYEditboxWin->subscribeEvent(CEGUI::Window::EventCharacterKey, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyCharacterKey, this));
    
    CEGUI::Window* guiGridZEditboxWin = guiRoot->getChild("RigMotionContainer/GridZContainer/GridZEditbox");
    guiGridZEditboxWin->subscribeEvent(CEGUI::Window::EventDeactivated, CEGUI::SubscriberSlot(&GUI::handleIntegerEditboxDeactive, this));
    guiGridZEditboxWin->subscribeEvent(CEGUI::Window::EventKeyDown, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyKeyDown, this));
    guiGridZEditboxWin->subscribeEvent(CEGUI::Window::EventCharacterKey, CEGUI::SubscriberSlot(&GUI::handleAllowNumbersOnlyCharacterKey, this));

    CEGUI::Window* guiResetMotionWin = guiRoot->getChild("RigMotionContainer/ResetContainer/ResetLabel");
    guiResetMotionWin->subscribeEvent(CEGUI::Window::EventMouseEntersArea, CEGUI::SubscriberSlot(&GUI::handleButtonLoopStart, this));
    guiResetMotionWin->subscribeEvent(CEGUI::Window::EventMouseLeavesArea, CEGUI::SubscriberSlot(&GUI::handleButtonLoopStop, this));
    guiResetMotionWin->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::SubscriberSlot(&GUI::handleResetMotionClick, this));

    CEGUI::Window* guiStartWin = guiRoot->getChild("StartQuitContainer/StartLabel");
    guiStartWin->subscribeEvent(CEGUI::Window::EventMouseEntersArea, CEGUI::SubscriberSlot(&GUI::handleButtonLoopStart, this));
    guiStartWin->subscribeEvent(CEGUI::Window::EventMouseLeavesArea, CEGUI::SubscriberSlot(&GUI::handleButtonLoopStop, this));
    guiStartWin->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::SubscriberSlot(&GUI::handleStartAppClick, this));
    
    CEGUI::Window* guiQuitWin = guiRoot->getChild("StartQuitContainer/QuitLabel");
    guiQuitWin->subscribeEvent(CEGUI::Window::EventMouseEntersArea, CEGUI::SubscriberSlot(&GUI::handleButtonLoopStart, this));
    guiQuitWin->subscribeEvent(CEGUI::Window::EventMouseLeavesArea, CEGUI::SubscriberSlot(&GUI::handleButtonLoopStop, this));
    guiQuitWin->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::SubscriberSlot(&GUI::handleQuitAppClick, this));

}

void GUI::loadDatafromSettings() {
    _logger->trace("Adding settings from ini file...");

    CEGUI::Window* guiRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

    guiRoot->getChild("RigMotionContainer/SerialPortContainer/SerialPortEditbox")->setText(this->config.getSerialPort());

    guiRoot->getChild("RigMotionContainer/FixedSettingsContainer/BaudEditbox")->setText(this->config.getBaud());
    guiRoot->getChild("RigMotionContainer/FixedSettingsContainer/FormatEditbox")->setText(this->config.getFormat());

    guiRoot->getChild("RigMotionContainer/SpeedXContainer/SpeedXEditbox")->setText(Settings::ftos(this->config.getSpeedX()));
    guiRoot->getChild("RigMotionContainer/SpeedYContainer/SpeedYEditbox")->setText(Settings::ftos(this->config.getSpeedY()));
    guiRoot->getChild("RigMotionContainer/SpeedZContainer/SpeedZEditbox")->setText(Settings::ftos(this->config.getSpeedZ()));
    guiRoot->getChild("RigMotionContainer/LengthXContainer/LengthXEditbox")->setText(Settings::ftos(this->config.getLengthX()));
    guiRoot->getChild("RigMotionContainer/LengthYContainer/LengthYEditbox")->setText(Settings::ftos(this->config.getLengthY()));
    guiRoot->getChild("RigMotionContainer/LengthZContainer/LengthZEditbox")->setText(Settings::ftos(this->config.getLengthZ()));
    
    guiRoot->getChild("RigMotionContainer/GridXContainer/GridXEditbox")->setText(Settings::itos(this->config.getGridX()));
    guiRoot->getChild("RigMotionContainer/GridYContainer/GridYEditbox")->setText(Settings::itos(this->config.getGridY()));
    guiRoot->getChild("RigMotionContainer/GridZContainer/GridZEditbox")->setText(Settings::itos(this->config.getGridZ()));

}

void GUI::openSerialPort() {
    if(link != NULL) return;

    CEGUI::Window* guiRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    
    CEGUI::Window* guiSerialPortLabel = guiRoot->getChild("RigMotionContainer/SerialPortContainer/SerialPortLabel");
    
    try {
        link = new UConLink(this->config.getSerialPort().c_str(), this->config.getBaud().c_str(), this->config.getFormat().c_str());

        guiSerialPortLabel->setProperty("NormalTextColour", "FF15DB3A");
        
    } catch (ucon_link::serial_file_open& e) {
        link = NULL;
        _logger->error(e.what());

        guiSerialPortLabel->setProperty("NormalTextColour", "FFDB1515");
    }
}

bool GUI::handleRefreshPortLoopStart(const CEGUI::EventArgs& args) {
    this->guiDynamicAnimInst.find("RefreshPortOver")->second->start();
    return false;
}

bool GUI::handleRefreshPortLoopStop(const CEGUI::EventArgs& args) {
    this->guiDynamicAnimInst.find("RefreshPortOver")->second->pause();
    return false;
}

bool GUI::handleRefreshPortClick(const CEGUI::EventArgs& args) {
    this->guiDynamicAnimInst.find("RefreshPortClick")->second->start();
    this->openSerialPort();
    return false;
}

bool GUI::handleSerialPortEditboxDeactive(const CEGUI::EventArgs& args) {
    CEGUI::String text;

    CEGUI::Window* guiRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();

    text = guiRoot->getChild("RigMotionContainer/SerialPortContainer/SerialPortEditbox")->getText();
    
    return false;
}

bool GUI::handleButtonLoopStart(const CEGUI::EventArgs& args) {
    CEGUI::String name;
    
    const CEGUI::WindowEventArgs& weargs = static_cast<const CEGUI::WindowEventArgs&>(args);

    name = weargs.window->getName();

    if(name == "ResetLabel")
        this->guiDynamicAnimInst.find("ResetMotionOver")->second->start();
    else if(name == "StartLabel")
        this->guiDynamicAnimInst.find("StartAppOver")->second->start();
    else if(name == "QuitLabel")
        this->guiDynamicAnimInst.find("QuitAppOver")->second->start();

    return false;
}

bool GUI::handleButtonLoopStop(const CEGUI::EventArgs& args) {
    CEGUI::String name;
    CEGUI::AnimationInstance* guiResetMotionOverAnimInst;

    const CEGUI::WindowEventArgs& weargs = static_cast<const CEGUI::WindowEventArgs&>(args);

    name = weargs.window->getName();

    if(name == "ResetLabel")    
        guiResetMotionOverAnimInst = this->guiDynamicAnimInst.find("ResetMotionOver")->second;
    else if(name == "StartLabel")
        guiResetMotionOverAnimInst = this->guiDynamicAnimInst.find("StartAppOver")->second;
    else if(name == "QuitLabel")
        guiResetMotionOverAnimInst = this->guiDynamicAnimInst.find("QuitAppOver")->second;
    
    guiResetMotionOverAnimInst->setPosition(guiResetMotionOverAnimInst->getDefinition()->getDuration());
    guiResetMotionOverAnimInst->apply();
    guiResetMotionOverAnimInst->stop();
    return false;
}

bool GUI::handleResetMotionClick(const CEGUI::EventArgs& args) {

    this->guiDynamicAnimInst.find("ResetMotionClick")->second->start();

    CEGUI::Window* guiRoot = CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow();
    
    CEGUI::Window* guiSpeedXEditboxWin = guiRoot->getChild("RigMotionContainer/SpeedXContainer/SpeedXEditbox");
    this->config.setSpeedX(Settings::x_axis_def_speed);
    guiSpeedXEditboxWin->setText(Settings::ftos(this->config.getSpeedX()));
    
    CEGUI::Window* guiSpeedYEditboxWin = guiRoot->getChild("RigMotionContainer/SpeedYContainer/SpeedYEditbox");
    this->config.setSpeedY(Settings::y_axis_def_speed);
    guiSpeedYEditboxWin->setText(Settings::ftos(this->config.getSpeedY()));
    
    CEGUI::Window* guiSpeedZEditboxWin = guiRoot->getChild("RigMotionContainer/SpeedZContainer/SpeedZEditbox");
    this->config.setSpeedZ(Settings::x_axis_def_speed);
    guiSpeedZEditboxWin->setText(Settings::ftos(this->config.getSpeedZ()));
    
    CEGUI::Window* guiLengthXEditboxWin = guiRoot->getChild("RigMotionContainer/LengthXContainer/LengthXEditbox");
    this->config.setLengthX(Settings::x_axis_def_length);
    guiLengthXEditboxWin->setText(Settings::ftos(this->config.getLengthX()));
    
    CEGUI::Window* guiLengthYEditboxWin = guiRoot->getChild("RigMotionContainer/LengthYContainer/LengthYEditbox");
    this->config.setLengthY(Settings::y_axis_def_length);
    guiLengthYEditboxWin->setText(Settings::ftos(this->config.getLengthY()));
    
    CEGUI::Window* guiLengthZEditboxWin = guiRoot->getChild("RigMotionContainer/LengthZContainer/LengthZEditbox");
    this->config.setLengthZ(Settings::z_axis_def_length);
    guiLengthZEditboxWin->setText(Settings::ftos(this->config.getLengthZ()));
    
    CEGUI::Window* guiGridXEditboxWin = guiRoot->getChild("RigMotionContainer/GridXContainer/GridXEditbox");
    this->config.setGridX(Settings::x_axis_def_grid);
    guiGridXEditboxWin->setText(Settings::itos(this->config.getGridX()));
    
    CEGUI::Window* guiGridYEditboxWin = guiRoot->getChild("RigMotionContainer/GridYContainer/GridYEditbox");
    this->config.setGridY(Settings::y_axis_def_grid);
    guiGridYEditboxWin->setText(Settings::itos(this->config.getGridY()));
    
    CEGUI::Window* guiGridZEditboxWin = guiRoot->getChild("RigMotionContainer/GridZContainer/GridZEditbox");
    this->config.setGridZ(Settings::z_axis_def_grid);
    guiGridZEditboxWin->setText(Settings::itos(this->config.getGridZ()));

    return true;    
}

bool GUI::handleStartAppClick(const CEGUI::EventArgs& args) {
    this->guiDynamicAnimInst.find("StartAppClick")->second->start();
    return true;
}

bool GUI::handleQuitAppClick(const CEGUI::EventArgs& args) {
    this->guiDynamicAnimInst.find("QuitAppClick")->second->start();
    return true;
}

bool GUI::handleQuit(const CEGUI::EventArgs& args) {
    this->device->closeDevice();
    return true;
}

bool GUI::handleStart(const CEGUI::EventArgs& args) {
    this->gui_active = false;
    return true;
}

bool GUI::handleFloatingEditboxDeactive(const CEGUI::EventArgs& args) {
    CEGUI::String name, text;
    float f_text;

    const CEGUI::WindowEventArgs& weargs = static_cast<const CEGUI::WindowEventArgs&>(args);

    name = weargs.window->getName();
    text = weargs.window->getText();

    if(text.length() >= 6) return true;

    if(text.length() > 0) f_text = std::stof(text.c_str());
    else f_text = 0;
   
    if(name == "SpeedXEditbox") {
        if(f_text > Settings::x_axis_max_speed) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::x_axis_max_speed)));
        }
        else if(f_text < Settings::x_axis_min_speed) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::x_axis_min_speed)));
        } else {
            weargs.window->setText(CEGUI::String(Settings::ftos(f_text)));
        }
        text = weargs.window->getText();
        f_text = std::stof(text.c_str());

        this->config.setSpeedX(f_text);

    } else if(name == "SpeedYEditbox") {
        if(f_text > Settings::y_axis_max_speed) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::y_axis_max_speed)));
        } else if(f_text < Settings::y_axis_min_speed) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::y_axis_min_speed))); 
        } else {
            weargs.window->setText(CEGUI::String(Settings::ftos(f_text)));
        }
        text = weargs.window->getText();
        f_text = std::stof(text.c_str());

        this->config.setSpeedY(f_text);

    } else if(name == "SpeedZEditbox") {
        if(f_text > Settings::z_axis_max_speed) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::z_axis_max_speed)));
        }
        else if(f_text < Settings::z_axis_min_speed) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::z_axis_min_speed)));
        } else {
            weargs.window->setText(CEGUI::String(Settings::ftos(f_text)));
        }
        text = weargs.window->getText();
        f_text = std::stof(text.c_str());

        this->config.setSpeedZ(f_text);

    } else if(name == "LengthXEditbox") {
        if(f_text > Settings::x_axis_max_length) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::x_axis_max_length)));
        }
        else if(f_text < Settings::x_axis_min_length) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::x_axis_min_length)));
        } else {
            weargs.window->setText(CEGUI::String(Settings::ftos(f_text)));
        }
        text = weargs.window->getText();
        f_text = std::stof(text.c_str());

        this->config.setLengthX(f_text);

    } else if(name == "LengthYEditbox") {
        if(f_text > Settings::y_axis_max_length) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::y_axis_max_length)));
        }
        else if(f_text < Settings::y_axis_min_length) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::y_axis_min_length)));
        } else {
            weargs.window->setText(CEGUI::String(Settings::ftos(f_text)));
        }
        text = weargs.window->getText();
        f_text = std::stof(text.c_str());

        this->config.setLengthY(f_text);

    } else if(name == "LengthZEditbox") {
        if(f_text > Settings::z_axis_max_length) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::z_axis_max_length)));
        }
        else if(f_text < Settings::z_axis_min_length) {
            weargs.window->setText(CEGUI::String(Settings::ftos(Settings::z_axis_min_length)));
        } else {
            weargs.window->setText(CEGUI::String(Settings::ftos(f_text)));
        }
        text = weargs.window->getText();
        f_text = std::stof(text.c_str());

        this->config.setLengthZ(f_text);

    }

    return false;

}

bool GUI::handleIntegerEditboxDeactive(const CEGUI::EventArgs& args) {
    CEGUI::String name, text;
    int i_text;

    const CEGUI::WindowEventArgs& weargs = static_cast<const CEGUI::WindowEventArgs&>(args);

    name = weargs.window->getName();
    text = weargs.window->getText();

    if(text.length() >= 6) return true;

    if(text.length() > 0) i_text = std::stoi(text.c_str());
    else i_text = 0;
   
    if(name == "GridXEditbox") {
        if(i_text > Settings::x_axis_max_grid) {
            weargs.window->setText(CEGUI::String(Settings::itos(Settings::x_axis_max_grid)));
        }
        else if(i_text < Settings::x_axis_min_grid) {
            weargs.window->setText(CEGUI::String(Settings::itos(Settings::x_axis_min_grid)));
        } else {
            weargs.window->setText(CEGUI::String(Settings::itos(i_text)));
        }
        text = weargs.window->getText();
        i_text = std::stoi(text.c_str());

        this->config.setGridX(i_text);
        
    } else if(name == "GridYEditbox") {
        if(i_text > Settings::y_axis_max_grid) {
            weargs.window->setText(CEGUI::String(Settings::itos(Settings::y_axis_max_grid)));
        } else if(i_text < Settings::y_axis_min_grid) {
            weargs.window->setText(CEGUI::String(Settings::itos(Settings::y_axis_min_grid))); 
        } else {
            weargs.window->setText(CEGUI::String(Settings::itos(i_text)));
        }
        text = weargs.window->getText();
        i_text = std::stoi(text.c_str());

        this->config.setGridY(i_text);

    } else if(name == "GridZEditbox") {
        if(i_text > Settings::z_axis_max_grid) {
            weargs.window->setText(CEGUI::String(Settings::itos(Settings::z_axis_max_grid)));
        }
        else if(i_text < Settings::z_axis_min_grid) {
            weargs.window->setText(CEGUI::String(Settings::itos(Settings::z_axis_min_grid)));
        } else {
            weargs.window->setText(CEGUI::String(Settings::itos(i_text)));
        }
        text = weargs.window->getText();
        i_text = std::stoi(text.c_str());

        this->config.setGridZ(i_text);
    }

    return false;

}

bool GUI::handleAllowNumbersOnlyKeyDown(const CEGUI::EventArgs& args) {
 
    const CEGUI::WindowEventArgs& weargs = static_cast<const CEGUI::WindowEventArgs&>(args);
    const CEGUI::KeyEventArgs& keargs = static_cast<const CEGUI::KeyEventArgs&>(args);

    switch(keargs.scancode) {
        case CEGUI::Key::Scan::Backspace :
            return false;
        case CEGUI::Key::Scan::Delete :
            return false;
        case CEGUI::Key::Scan::ArrowRight :
            return false;
        case CEGUI::Key::Scan::ArrowLeft :
            return false;
        case CEGUI::Key::Scan::Return :
            weargs.window->deactivate();
            return false;

    }

    return true;

}

bool GUI::handleAllowNumbersOnlyCharacterKey(const CEGUI::EventArgs& args) {
    CEGUI::String name, text;
    
    const CEGUI::WindowEventArgs& weargs = static_cast<const CEGUI::WindowEventArgs&>(args);
    const CEGUI::KeyEventArgs& keargs = static_cast<const CEGUI::KeyEventArgs&>(args);

    switch(keargs.scancode) {
        case CEGUI::Key::Scan::One : 
            return false;
        case CEGUI::Key::Scan::Two :
            return false;
        case CEGUI::Key::Scan::Three :
            return false;
        case CEGUI::Key::Scan::Four :
            return false;
        case CEGUI::Key::Scan::Five :
            return false;
        case CEGUI::Key::Scan::Six :
            return false;
        case CEGUI::Key::Scan::Seven :
            return false;
        case CEGUI::Key::Scan::Eight :
            return false;
        case CEGUI::Key::Scan::Nine :
            return false;
        case CEGUI::Key::Scan::Zero :
            return false;
        case CEGUI::Key::Scan::Period :
            name = weargs.window->getName();
            if(name.find("Grid") == CEGUI::String::npos){
                text = weargs.window->getText();
                if(text.find(".") == CEGUI::String::npos) return false;
            }
    }

    return true;

}

GUI::~GUI() {
    _logger->trace("Exiting...");

    CEGUI::IrrlichtRenderer::destroySystem();
    this->device->drop();
    spdlog::drop("GUI");
    this->guiStaticAnimInst.clear();
    this->guiDynamicAnimInst.clear();

    if(this->link != NULL)
        delete this->link;
}
