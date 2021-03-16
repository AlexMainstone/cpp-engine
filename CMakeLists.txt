cmake_minimum_required(VERSION 3.0)
project(cpp-engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

SET (CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG_")
SET (CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")

# C++17
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    # Game Loop
    src/Main.cpp
    
    # Scenes
    src/Scenes/GameScene.cpp
    )


# find_package(ImGui-SFML) # debug
find_package(SFML 2.5 REQUIRED audio graphics window system)
# find_package(TMXLITE REQUIRED)

set(ENTT_INCLUDE "${CMAKE_SOURCE_DIR}/libs/entt-master/include" CACHE PATH "Path to include directory of EnTT")

add_executable(cpp-engine ${SOURCES})

include_directories(cpp-engine PRIVATE ${CMAKE_SOURCE_DIR}/include ${ENTT_INCLUDE} )

target_link_libraries(cpp-engine sfml-audio sfml-graphics sfml-window sfml-system sfml-network)