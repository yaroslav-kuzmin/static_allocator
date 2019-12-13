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
#SIZE_BLOCK_POWER2 - размер блока в байтах указывается степень двойки
#NUMBER_BLOCK      - колличество блоков
#NUMBER_BITMAP     - колличество блоков деленое на 32 бита, информация о блокох хранится в массиве uint32_t по битно, 
#ADDRESS_BLOCK     - адрес начала блока данных, если 0 то выделяет массив
target_compile_options(${PROJECT_NAME} PUBLIC -DSIZE_BLOCK_POWER2=3 -DNUMBER_BLOCK=30 -DNUMBER_BITMAP=1 -DADDRESS_BLOCK=0)
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR})

