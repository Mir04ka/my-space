cmake_minimum_required(VERSION 4.0)
project(spaceSim)

set(CMAKE_CXX_STANDARD 23)

find_package(raylib REQUIRED)

add_executable(spaceSim main.cpp
        object/Object.cpp
        object/Object.h
        types/Constants.h
        types/Vector2d.h)
target_include_directories(spaceSim PRIVATE libs/raygui)
target_link_libraries(spaceSim raylib m dl pthread GL rt X11)