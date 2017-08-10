/**
 * File              : src/freenect_grabber.cc
 * Author            : Siddharth J. Singh <j.singh.logan@gmail.com>
 * Date              : 10.08.2017
 * Last Modified Date: 11.08.2017
 * Last Modified By  : Siddharth J. Singh <j.singh.logan@gmail.com>
 */
/**
 * freenect_grabber.cc
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

#include "freenect_grabber.h"

FreenectGrabber::FreenectGrabber() : DataGrabber("FreenectGrabber"){
    //TODO: Initialize this from a file possibly
    __logger()->set_level(spdlog::level::trace);

    freenect_context *ctx;
    int retval;
    retval = freenect_init(&ctx, NULL);

    if(retval == 0) {
        __logger()->trace("Initialized freenect API.");
    } else {
        __logger()->error("Couldn't initiate freenect API!!!");
        exit(retval);
    }

    freenect_set_log_level(ctx, FREENECT_LOG_DEBUG);
    freenect_select_subdevices(ctx, FREENECT_DEVICE_CAMERA);

    retval = freenect_num_devices(ctx);
    
    if(retval) {
        __logger()->trace("{0} Kinect device(s) is(are) connected to the system.", retval);
    } else {
        __logger()->error("No Kinect devices are connected!!!");
        __logger()->error("Please check the device power and connectivity.");
        freenect_shutdown(ctx);
        exit(retval);
    }

    //TODO: Make this function generic for many cameras
    freenect_device *dev;
    retval = freenect_open_device(ctx, &dev, -1); 

    if(retval == 0) {
        __logger()->trace("Camera opened for RGB transfer.", retval);
    } else {
        __logger()->error("Device couldn't be opened!!!");
        freenect_shutdown(ctx);
        exit(retval);
    }

    retval = freenect_set_video_mode(dev, freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB));
    
    if(retval == 0) {
        __logger()->trace("Video mode was set correctly.");
    } else {
        __logger()->error("Could not set the video mode!!!");
        freenect_close_device(dev);
        freenect_shutdown(ctx);
    }


    //retval = freenect_set_video_buffer(dev, 

    freenect_close_device(dev);
    freenect_shutdown(ctx);
}

void FreenectGrabber::grab_image(cv::Mat& image) {
/*    __logger()->info("INFO");
    __logger()->trace("TRACE");
    __logger()->error("ERROR");
    __logger()->debug("DEBUG");
    __logger()->warn("WARNING");
    __logger()->critical("CRITICAL");
    __logger()->error("ERROR");*/
    image.clone();
}


