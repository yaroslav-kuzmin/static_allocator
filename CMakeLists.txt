##############################################################################
#                                                                            #
# allocator : Модуль блочного выделения памяти                               #
#                                                                            #
#  Copyright (C) 2019 Kuzmin Yaroslav <kuzmin.yaroslav@gmail.com>            #
#                                                                            #
# allocator is free software: you can redistribute it and/or modify it       #
# under the terms of the GNU General Public License as published by the      #
# Free Software Foundation, either version 3 of the License, or              #
# (at your option) any later version.                                        #
#                                                                            #
# allocator is distributed in the hope that it will be useful, but           #
# WITHOUT ANY WARRANTY; without even the implied warranty of                 #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       #
# See the GNU General Public License for more details.                       #
#                                                                            #
# You should have received a copy of the GNU General Public License along    #
# with this program.  If not, see <http://www.gnu.org/licenses/>.            #
#                                                                            #
##############################################################################

cmake_minimum_required(VERSION 3.15)

project(allocator VERSION 0.0.1 LANGUAGES C)
set(CMAKE_C_COMPILER_WORK true)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER_WORK false)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)


if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_C_FLAGS "-O2 -std=gnu99")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_C_FLAGS "-std=gnu99 -g2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "DebugProf")
  set(CMAKE_C_FLAGS "-std=gnu99 -g2 -pg")
endif()

enable_testing()

add_subdirectory(src)
add_subdirectory(test)



