project(rlogStub)
cmake_minimum_required(VERSION 2.6)

include_directories(~/rlog-1.4)

add_definitions(-std=c++0x)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -DRLOG_COMPONENT=debug -Wall")
set(sources rlog.cpp RLogChannel.cpp RLogNode.cpp StdioNode.cpp)
add_library(rlogStub ${sources})

target_link_libraries(rlogStub pthread)
target_link_libraries(rlogStub rt)

