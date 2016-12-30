cmake_minimum_required(VERSION 2.8)

get_filename_component(BASENAME ${CMAKE_SOURCE_DIR} NAME)
project(${BASENAME})

find_package(OpenCV)

#include
include_directories("inc")
include_directories(${OpenCV_INCLUDE_DIRS})

aux_source_directory(src SRC_FILES)
add_executable(${PROJECT_NAME} ${SRC_FILES})

#bin
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})