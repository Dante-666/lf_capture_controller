/**
 * File              : inc/gui.h
 * Author            : Siddharth J. Singh <j.singh.logan@gmail.com>
 * Date              : 04.10.2017
 * Last Modified Date: 04.10.2017
 * Last Modified By  : Siddharth J. Singh <j.singh.logan@gmail.com>
 */

/**
 * inc/gui.h
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

#ifndef __GUI_H_
#define __GUI_H_

#include <iomanip>
#include <sstream>

#include <irrlicht/irrlicht.h>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Irrlicht/EventPusher.h>
#include <CEGUI/RendererModules/Irrlicht/Renderer.h>

#include <spdlog/spdlog.h>

#include "ucon_link.h"

#define IRR_ORIGIN      irr::core::vector3df(0, 0, 0)
#define SHAFT_Y_OFFEST  irr::core::vector3df(0, 552.5, 0) 
#define COUPLING_OFFSET irr::core::vector3df(-28.78, 85, 47)
#define RAIL_OFFSET     irr::core::vector3df(0, 495, 0)

#define LEFT_OFFSET     irr::core::vector3df(-28.78, 85, 47)

#define RIGHT_OFFSET    irr::core::vector3df(0, 0, -1300)
#define RIGHT_ROTATION  irr::core::vector3df(0, 180, 0)

#define HORIZ_OFFSET    irr::core::vector3df(0, 120, -126)
#define HORIZ_ROTATION  irr::core::vector3df(90, 180, 0) 

class Settings {
    public:
        Settings();
        ~Settings();
        
        void setSerialPort(std::string port);
        std::string getSerialPort();
        void setBaud(std::string baud);
        std::string getBaud();
        void setFormat(std::string format);
        std::string getFormat();
        void setSpeedX(float speed);
        float getSpeedX();
        void setLengthX(float length);
        float getLengthX();
        void setSpeedY(float speed);
        float getSpeedY();
        void setLengthY(float length);
        float getLengthY();
        void setSpeedZ(float speed);
        float getSpeedZ();
        void setLengthZ(float length);
        float getLengthZ();

        void setGridX(int size);
        void setGridY(int size);
        void setGridZ(int size);
        int getGridX();
        int getGridY();
        int getGridZ();

        void readData();
        void writeback();

        static std::string ftos(float input);
        static std::string itos(int input);

        /*-- Fallback and Limits --*/
        static constexpr float x_axis_max_speed = 30.f;
        static constexpr float y_axis_max_speed = 30.f;
        static constexpr float z_axis_max_speed = 15.f;
        static constexpr float x_axis_max_length = 30.f;
        static constexpr float y_axis_max_length = 30.f;
        static constexpr float z_axis_max_length = 15.f;
        static constexpr int x_axis_max_grid = 50;
        static constexpr int y_axis_max_grid = 50;
        static constexpr int z_axis_max_grid = 20;

        static constexpr float x_axis_def_speed = 10.f;
        static constexpr float y_axis_def_speed = 10.f;
        static constexpr float z_axis_def_speed = 5.f;
        static constexpr float x_axis_def_length = 10.f;
        static constexpr float y_axis_def_length = 10.f;
        static constexpr float z_axis_def_length = 5.f;
        static constexpr int x_axis_def_grid = 13;
        static constexpr int y_axis_def_grid = 13;
        static constexpr int z_axis_def_grid = 5;

        static constexpr float x_axis_min_speed = 1.f;
        static constexpr float y_axis_min_speed = 1.f;
        static constexpr float z_axis_min_speed = 1.f;
        static constexpr float x_axis_min_length = 1.f;
        static constexpr float y_axis_min_length = 1.f;
        static constexpr float z_axis_min_length = 1.f;
        static constexpr int x_axis_min_grid = 5;
        static constexpr int y_axis_min_grid = 5;
        static constexpr int z_axis_min_grid = 1;

    private:
        std::fstream cfg_file;
        /*-- Serial Communication --*/
        std::string serial_port;
        std::string baud;
        std::string format;
        
        float x_axis_speed;
        float y_axis_speed;
        float z_axis_speed;       
        float x_axis_length;
        float y_axis_length;
        float z_axis_length;

        /*-- Trajectory Settings --*/
        int x_grid;
        int y_grid;
        int z_grid;

        /*-- Camera Settings --*/

        std::shared_ptr<spdlog::logger> _logger;
};

class GUI : private irr::IEventReceiver {
    public:
        GUI();
        ~GUI();

        void init();
    private:
        bool OnEvent(const irr::SEvent& event);
        
        bool readConfigFile();

        void initFrequencyLookup();

        float convertMMtoHz(float mmps);
        float convertHztoMM(float hz);

        void processMotionCommands(float delta_t);
        
        void move_x(irr::scene::ISceneNode* rotary_node_x, irr::scene::ISceneNode* linear_node_x,
                    float rotary_speed, float delta_t);
        void move_y(irr::scene::ISceneNode* rotary_node_y_l, irr::scene::ISceneNode* linear_node_y_l,
                    irr::scene::ISceneNode* rotary_node_y_r, irr::scene::ISceneNode* linear_node_y_r,
                    float rotary_speed, float delta_t);

        //Add more as you go, helper functions
        void addShaders();
        void addLightsandCameras();
        void addMeshes();
        void createFrame();

        /*-- Camera Helpers --*/
        void cameraZoomIn(bool rapid);
        void cameraZoomOut(bool rapid);
        void cameraRotate(bool rapid, irr::core::position2df mousePos);

        /*-- CEGUI Functions --*/
        void bootstrapCEGUI();
        void setupStaticAnimation();
        void startStaticAnimation();
        void setupDynamicAnimation();
        void setupDynamicEvents();
        void loadDatafromSettings();

        /*-- CEGUI Event Handlers --*/
        bool handleRefreshPortLoopStart(const CEGUI::EventArgs& args);
        bool handleRefreshPortLoopStop(const CEGUI::EventArgs& args);
        bool handleRefreshPortClick(const CEGUI::EventArgs& args);
        bool handleSerialPortEditboxDeactive(const CEGUI::EventArgs& args);
        
        bool handleButtonLoopStart(const CEGUI::EventArgs& args);
        bool handleButtonLoopStop(const CEGUI::EventArgs& args);
        bool handleResetMotionClick(const CEGUI::EventArgs& args);
        bool handleStartAppClick(const CEGUI::EventArgs& args);
        bool handleQuitAppClick(const CEGUI::EventArgs& args);
        bool handleStart(const CEGUI::EventArgs& args);
        bool handleQuit(const CEGUI::EventArgs& args);
        
        bool handleAllowNumbersOnlyKeyDown(const CEGUI::EventArgs& args);
        bool handleAllowNumbersOnlyCharacterKey(const CEGUI::EventArgs& args);
        bool handleFloatingEditboxDeactive(const CEGUI::EventArgs& args);
        bool handleIntegerEditboxDeactive(const CEGUI::EventArgs& args);

        /*-- Motion Controller helpers --*/
        void openSerialPort();

        /*-- Persistance --*/
        Settings config;

        /*-- Engine --*/ 
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver *driver;
        irr::scene::ISceneManager *smgr;
        irr::scene::ICameraSceneNode *cam;
        irr::scene::ILightSceneNode *light;
        irr::gui::ICursorControl *cursor;

        irr::f32 shift_multiplier = 5.0;
        irr::f32 cam_zoom_speed = 5.0;
        irr::f32 cam_rotate_speed = 5.0;
        
        /*-- Shaders --*/
        irr::s32 toon_black_metal_shader;
        irr::s32 toon_silver_metal_shader;
        irr::s32 toon_gold_metal_shader;
        irr::s32 toon_blue_metal_shader;
        irr::s32 toon_green_metal_shader;

        /*-- Mesh --*/
        irr::scene::IAnimatedMesh* start_shaft_holder;
        irr::scene::IAnimatedMesh* finish_shaft_holder;
        irr::scene::IAnimatedMesh* motor_shaft_link;
        irr::scene::IAnimatedMesh* motor;
        irr::scene::IAnimatedMesh* steel_rail;
        irr::scene::IAnimatedMesh* aluminium_back;
        irr::scene::IAnimatedMesh* finish_bearing;
        irr::scene::IAnimatedMesh* start_bearing;

        irr::scene::IAnimatedMesh* rail_top;
        irr::scene::IAnimatedMesh* rail_ball_screw;
        irr::scene::IAnimatedMesh* rail_clamp;

        irr::scene::IAnimatedMesh* shaft;
        irr::scene::IAnimatedMesh* coupling;
       
        /*-- Nodes --*/
        irr::scene::ISceneNode* linear_guide_node[3];
        irr::scene::ISceneNode* linear_rail_node[3];
        irr::scene::ISceneNode* rotational_shaft_node[3];

        irr::scene::ISceneNode* start_shaft_holder_node[3];
        irr::scene::ISceneNode* finish_shaft_holder_node[3];
        irr::scene::ISceneNode* motor_shaft_link_node[3];
        irr::scene::ISceneNode* motor_node[3];
        irr::scene::ISceneNode* steel_rail_node[3];
        irr::scene::ISceneNode* aluminium_back_node[3];
        irr::scene::ISceneNode* finish_bearing_node[3];
        irr::scene::ISceneNode* start_bearing_node[3];
        
        irr::scene::ISceneNode* rail_top_node[3];
        irr::scene::ISceneNode* rail_ball_screw_node[3];
        irr::scene::ISceneNode* rail_clamp_node[3];

        irr::scene::ISceneNode* shaft_node[3];
        irr::scene::ISceneNode* coupling_node[3];

        /*-- For detecting key toggle --*/
        /*
         * 0    -> BACKSPACE    -> Switch GUI Context TODO: Change to ESCAPE later
         * 1    ->      HOME    -> Motion-Y Up
         * 2    ->       END    -> Motion-Y Down
         * 3    ->   PG_DOWN    -> Motion-X Forward
         * 4    ->    DELETE    -> Motion-X Backward
         * 5    ->     PG_UP    -> Motion-Z Forward
         * 6    ->    INSERT    -> Motion-Z Backward
         *
         * Reduce index by 1 for MovementState
         */
        bool motionKeyState[7];
        bool motionMovementState[6];

        float frequencyLookup[256];


        /*-- CEGUI --*/
        CEGUI::IrrlichtRenderer* guiRend;
        std::vector<CEGUI::AnimationInstance *> guiStaticAnimInst;
        std::map<std::string, CEGUI::AnimationInstance *> guiDynamicAnimInst;
        bool gui_active = true;
        bool hide_cam = true;

        /*-- Motion Controller --*/
        UConLink* link = NULL;

        std::shared_ptr<spdlog::logger> _logger;

};

#endif //__GUI_H_
