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

set(SOURCES allocator.c)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include) 

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_compile_options(${PROJECT_NAME} PUBLIC -DSIZE_BLOCK=16 -DNUMBER_BLOCK=10 -DADDRESS_BLOCK=0)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

