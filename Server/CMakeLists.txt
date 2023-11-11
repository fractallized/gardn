cmake_minimum_required(VERSION 3.16)
project(gardn-server)

include_directories(..)

set(SOURCES
    System/Velocity.cc
    Main.cc
    Server.cc
    Simulation.cc
    ../Shared/Simulation.cc
    ../Shared/Utilities.cc
)

set(CMAKE_CXX_FLAGS "-std=c++17 -gdwarf-4 -lpthread -DSERVER_SIDE=1")
# set(CMAKE_CXX_FLAGS "-std=c++17 -O3 -lpthread")
set(CMAKE_CXX_COMPILER "clang++")

add_executable(gardn-server ${SOURCES})
if(WINDOWS)
    target_link_directories(gardn-server PRIVATE /c/libwebsockets/unix-build/bin)
    target_link_libraries(gardn-server ws2_32 wsock32)
endif()
if (SERVER)
endif()
target_link_libraries(gardn-server pthread websockets m)
