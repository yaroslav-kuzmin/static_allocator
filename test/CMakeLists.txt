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

set(TEST_NAME test_main)
set(TEST_SRC ${TEST_NAME}.c)
add_executable(${TEST_NAME} ${TEST_SRC})
target_link_libraries(${TEST_NAME} ${PROJECT_NAME})
target_compile_options(${TEST_NAME} PUBLIC -DSIZE_BLOCK=16 -DNUMBER_BLOCK=10 -DADDRESS_BLOCK=0)
target_include_directories(${TEST_NAME} PUBLIC ${INCLUDE_DIR})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})	
	
set(TEST_NAME test_bitmap)
set(TEST_SRC ${TEST_NAME}.c)
add_executable(${TEST_NAME} ${TEST_SRC} ${SOURCE})
target_compile_options(${TEST_NAME} PUBLIC -DSIZE_BLOCK=16 -DNUMBER_BLOCK=100 -DADDRESS_BLOCK=0)
target_include_directories(${TEST_NAME} PUBLIC ${INCLUDE_DIR})
add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})	
	
