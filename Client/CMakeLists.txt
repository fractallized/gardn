set(CMAKE_SYSTEM_NAME Generic)
cmake_minimum_required(VERSION 3.16)

project(gardn-client)

include_directories(../Client)

set(SOURCES
    Game.cc
    Main.cc
    Renderer.cc
)

# no assertions in wasm build
set(CMAKE_CXX_FLAGS "-std=c++20 -gdwarf-4 -s EXPORTED_FUNCTIONS=_main,_malloc,_free,_render")
set(CMAKE_CXX_COMPILER "em++")
add_executable(gardn-client ${SOURCES})