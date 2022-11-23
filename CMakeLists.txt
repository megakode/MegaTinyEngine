cmake_minimum_required(VERSION 3.16)
project(MTEngine)

set(CMAKE_CXX_STANDARD 17)

#set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} C:/Users/peter/Code/libs/SDL2-2.0.12/ C:/Users/peter/Code/libs/SDL2_image-2.0.5/)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

ADD_LIBRARY(${PROJECT_NAME} STATIC)
add_subdirectory(MegaTinyEngine)

target_include_directories(${PROJECT_NAME} PRIVATE .)
target_include_directories(${PROJECT_NAME} INTERFACE .)
target_include_directories(${PROJECT_NAME} PRIVATE Vendor)
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::Image)

add_subdirectory(examples)