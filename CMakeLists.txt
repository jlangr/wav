project(SnippetPublisher)
cmake_minimum_required(VERSION 2.6)

include_directories(~/boost_1_51_0 ~/rlog-1.4 ~/cpputest/include)
link_directories(~/rlog-1.4/rlog/.libs ~/cpputest)

add_definitions(-std=c++0x)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -DRLOG_COMPONENT=debug -Wall")
set(sources WavReader.cpp WavDescriptor.cpp)
set(testSources WavReaderTest.cpp)
add_executable(utest testmain.cpp ${testSources} ${sources})
add_executable(SnippetPublisher main.cpp ${sources})

find_package(Boost 1.51.0 COMPONENTS filesystem system)
target_link_libraries(utest ${Boost_LIBRARIES})
target_link_libraries(utest CppUTest)
target_link_libraries(utest pthread)
target_link_libraries(utest rt)
target_link_libraries(utest rlog)

target_link_libraries(SnippetPublisher ${Boost_LIBRARIES})
target_link_libraries(SnippetPublisher pthread)
target_link_libraries(SnippetPublisher rt)
target_link_libraries(SnippetPublisher rlog)

