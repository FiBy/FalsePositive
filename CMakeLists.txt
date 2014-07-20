project(FalsePositive)
cmake_minimum_required(VERSION 2.8)
include_directories(./inc)
set(SRC_LIST
    src/main.cpp
    src/Engine/MapTile.cpp )
set(INC_LIST
    inc/main.hpp
    inc/Engine/MapTile.hpp )
add_executable(${PROJECT_NAME} ${SRC_LIST} ${INC_LIST})

find_package(SFML REQUIRED system window graphics network audio)
add_definitions(-std=c++11)
SET(LIBS ${LIBS} ${SFML_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
