/**
 * File              : src/freenect_grabber.cc
 * Author            : Siddharth J. Singh <j.singh.logan@gmail.com>
 * Date              : 10.08.2017
 * Last Modified Date: 10.08.2017
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

FreenectGrabber::FreenectGrabber() {
    _logger = spdlog::stdout_color_mt("FreenectGrabber");
}

void FreenectGrabber::grab_image() {
    _logger->info("in grab_image");
}


