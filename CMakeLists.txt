cmake_minimum_required(VERSION 3.5)
project(PRO2_PRAC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#add_executable(PRO2_PRAC ${SOURCE_FILES})
add_custom_target(PRO2_PRAC ALL COMMAND make WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} )