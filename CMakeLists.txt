project(FalsePositive)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/SFML/cmake/Modules/" "/usr/local/share/SFML/cmake/Modules/")
include_directories(./inc)
set(SRC_LIST
    src/main.cpp
	src/Engine/Engine.cpp
    src/Engine/Map.cpp
	src/Engine/MapComponent.cpp
	src/Engine/MapPortal.cpp
	src/Engine/MapTile.cpp
	src/Engine/PathNode.cpp
	src/Engine/Person.cpp
	src/Engine/Resources.cpp
	src/Engine/SFMLext.cpp
)
set(INC_LIST
    inc/main.hpp
	inc/Engine/Engine.hpp
	inc/Engine/Map.hpp
	inc/Engine/MapComponent.hpp
	inc/Engine/MapPortal.hpp
	inc/Engine/MapTile.hpp
	inc/Engine/PathNode.hpp
	inc/Engine/Person.hpp
	inc/Engine/Resources.hpp
	inc/Engine/SFMLext.hpp
)
add_executable(${PROJECT_NAME} ${SRC_LIST} ${INC_LIST})

if(DEFINED CMAKE_BUILD_TYPE)
	if(CMAKE_BUILD_TYPE STREQUAL "Release")
		add_definitions(-O3)
		MESSAGE ("Doing release compile, using optimization flags.")
	else()
		add_definitions(-g -Wall -DDEBUG)
		MESSAGE ("Doing debug compile, including debug symbols.")
	endif()
endif()

find_package(SFML REQUIRED system window graphics network audio)
add_definitions(-std=c++11)
SET(LIBS ${LIBS} ${SFML_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
