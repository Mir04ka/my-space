cmake_minimum_required(VERSION 3.31)
project(mySpace)

set(CMAKE_CXX_STANDARD 23)

find_package(raylib REQUIRED)

add_executable(mySpace main.cpp
        object/Object.cpp
        object/Object.h
        types/Vector2d.h
        types/Constants.h)
target_link_libraries(mySpace raylib m dl pthread GL rt X11)
