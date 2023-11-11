cmake_minimum_required(VERSION 3.16)
project(gardn-server)

include_directories(..)
include_directories(/c/libuv/include)

set(SOURCES
    Main.cc
)

set(CMAKE_CXX_FLAGS "-std=c++17 -gdwarf-4 -lpthread")
# set(CMAKE_CXX_FLAGS "-std=c++17 -O3 -lpthread")
set(CMAKE_CXX_COMPILER "clang++")

add_executable(gardn-server ${SOURCES})
if(WINDOWS)
    target_link_libraries(gardn-server ws2_32 wsock32)
endif()
target_link_libraries(gardn-server pthread uv)
