#
# CMakeLists.txt
#
# Created by Jean-Pierre Höhmann on 18-08-25.
#
# Copyright 2018 Jean-Pierre Höhmann (@NuvandaPV) <jean-pierre@höhmann.info>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

#
# Stub CMakeLists for IDEs that need it.
#

project(mivios)
cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_C_FLAGS "-std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_VERBOSE_MAKEFILE  on)

# CMake will complain, that “install” and “clean” are reserved, but it will run fine.
# TODO Maybe make this pretty some day, if i feel like figuring out CMake.
# FIXME Many IDE features will not work since this file does not provide the IDE with any useful info whatsoever.
add_custom_target(${PROJECT_NAME} COMMAND cd ${${PROJECT_NAME}_SOURCE_DIR} && TARGET=${CMAKE_BUILD_TYPE} ./build.sh)
add_custom_target(install COMMAND cd ${${PROJECT_NAME}_SOURCE_DIR} && TARGET=${CMAKE_BUILD_TYPE} ./install.sh)
add_custom_target(clean COMMAND cd ${${PROJECT_NAME}_SOURCE_DIR} && TARGET=${CMAKE_BUILD_TYPE} ./clean.sh)
