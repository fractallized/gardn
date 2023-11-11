set(CMAKE_SYSTEM_NAME Generic)
cmake_minimum_required(VERSION 3.16)

project(gardn-client)

include_directories(../Client)
include_directories(../)

set(SOURCES
    Game.cc
    Main.cc
    Renderer.cc
    Simulation.cc
    ../Shared/Simulation.cc
    ../Shared/Utilities.cc
)

# no assertions in wasm build
set(CMAKE_CXX_FLAGS "-std=c++20 -DCLIENT=1 -gdwarf-4 -s EXPORTED_FUNCTIONS=_main,_malloc,_free,_render")
set(CMAKE_CXX_COMPILER "em++")
add_executable(gardn-client ${SOURCES})