cmake_minimum_required(VERSION 3.16)
project(MTEngine)

set(CMAKE_CXX_STANDARD 14)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

ADD_LIBRARY(MTEngine STATIC
        MegaTinyEngine/Collision/BoxCollider.cpp
		MegaTinyEngine/Collision/BoxCollider.h
        MegaTinyEngine/Collision/CollisionManager.cpp
        MegaTinyEngine/Collision/CollisionManager.h
        MegaTinyEngine/Resources/JSONSerialization.h
        MegaTinyEngine/Resources/ResourceFile.h
        MegaTinyEngine/Resources/ResourceLoader.cpp
        MegaTinyEngine/Resources/ResourceLoader.h
        Vendor/json.hpp
        MegaTinyEngine/Animation.h
        MegaTinyEngine/AnimationManager.cpp
        MegaTinyEngine/AnimationManager.h
        MegaTinyEngine/Base.h
        MegaTinyEngine/Camera.cpp
        MegaTinyEngine/Camera.h
        MegaTinyEngine/Core.cpp
        MegaTinyEngine/Core.h
        MegaTinyEngine/GameObject.cpp
        MegaTinyEngine/GameObject.h
        MegaTinyEngine/InputManager.cpp
        MegaTinyEngine/InputManager.h
        MegaTinyEngine/KinematicBody.cpp
        MegaTinyEngine/KinematicBody.h
        MegaTinyEngine/Rect.h
        MegaTinyEngine/Settings.cpp
        MegaTinyEngine/Settings.h
        MegaTinyEngine/Sprite.cpp
        MegaTinyEngine/Sprite.h
        MegaTinyEngine/SpriteFrame.h
        MegaTinyEngine/TextNode.cpp
        MegaTinyEngine/TextNode.h
        MegaTinyEngine/Texture.cpp
        MegaTinyEngine/Texture.hpp
        MegaTinyEngine/TextureCache.cpp
        MegaTinyEngine/TextureCache.h MegaTinyEngine/IGame.h)

target_include_directories(MTEngine PRIVATE .)

target_include_directories(MTEngine INTERFACE .)


target_link_libraries(MTEngine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

