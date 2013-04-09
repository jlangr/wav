project(rlogStub)
cmake_minimum_required(VERSION 2.6)

include_directories($ENV{RLOG_HOME})

add_definitions(-std=c++0x)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -DRLOG_COMPONENT=debug -Wall")
set(sources StdioNode.cpp)
add_library(rlogStub ${sources})

target_link_libraries(rlogStub pthread)

