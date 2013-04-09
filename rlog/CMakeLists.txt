project(rlogStub)
cmake_minimum_required(VERSION 2.6)

include_directories($ENV{RLOG_HOME})

add_definitions(-std=c++0x)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -DRLOG_COMPONENT=debug -Wall")
# START:sources
set(sources rlog.cpp RLogChannel.cpp RLogNode.cpp StdioNode.cpp)
# END:sources
add_library(rlogStub ${sources})

target_link_libraries(rlogStub pthread)

