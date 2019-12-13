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
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(SOURCE ${SOURCE_DIR}/allocator.c)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

#SIZE_BLOCK_POWER2 - размер блока в байтах указывается степень двойки
#NUMBER_BLOCK      - колличество блоков
#NUMBER_BITMAP     - колличество блоков деленое на 32 бита, информация о блокох хранится в массиве uint32_t по битно,
#ADDRESS_BLOCK     - адрес начала блока данных, если 0 то выделяет массив
set(TEST_NAME test_main)
set(TEST_SRC ${TEST_NAME}.c)
add_executable(${TEST_NAME} ${TEST_SRC})
set(TEST_NAME_LIB ${TEST_NAME}_${PROJECT_NAME})
add_library(${TEST_NAME_LIB} ${SOURCE})
target_link_libraries(${TEST_NAME} ${TEST_NAME_LIB})
target_compile_options(${TEST_NAME_LIB} PUBLIC -DSIZE_BLOCK_POWER2=3 -DNUMBER_BLOCK=10 -DNUMBER_BITMAP=1 -DADDRESS_BLOCK=0)
target_include_directories(${TEST_NAME} PUBLIC ${INCLUDE_DIR})
target_include_directories(${TEST_NAME_LIB} PUBLIC ${INCLUDE_DIR})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

set(TEST_NAME test_bitmap)
set(TEST_SRC ${TEST_NAME}.c)
add_executable(${TEST_NAME} ${TEST_SRC} ${SOURCE})
target_compile_options(${TEST_NAME} PUBLIC -DSIZE_BLOCK_POWER2=3 -DNUMBER_BLOCK=100 -DNUMBER_BITMAP=4 -DADDRESS_BLOCK=0)
target_include_directories(${TEST_NAME} PUBLIC ${INCLUDE_DIR})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})

