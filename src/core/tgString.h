/*
 * Copyright © 2012, United States Government, as represented by the
 * Administrator of the National Aeronautics and Space Administration.
 * All rights reserved.
 * 
 * The NASA Tensegrity Robotics Toolkit (NTRT) v1 platform is licensed
 * under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0.
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
*/

#include <string>
#include <sstream>

/**
 * @file tgString.h
 * @brief Convenience function for combining strings with ints, mostly for naming structures
 * @date March 2014
 */

/**
 * Convenience function for combining strings with ints, mostly for naming structures
 */
 // 4_3_14 - made inline to prevent odd linker errors _BRT
inline std::string tgString(std::string s, int i)
{
    std::ostringstream ss;
    ss << s << i;
    return ss.str();
}
