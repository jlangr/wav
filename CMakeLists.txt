project(SnippetPublisher)
cmake_minimum_required(VERSION 2.6)

include_directories($ENV{BOOST_ROOT}/ $ENV{RLOG_HOME} $ENV{CPPUTEST_HOME}/include)
link_directories($ENV{RLOG_HOME}/rlog/.libs $ENV{CPPUTEST_HOME}/lib) 
set(Boost_USE_STATIC_LIBS ON)

add_subdirectory(rlog)

add_definitions(-std=c++0x)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -DRLOG_COMPONENT=debug -Wall")
set(sources FileUtil.cpp StreamUtil.cpp WavReader.cpp WavDescriptor.cpp)
set(testSources FileUtilTest.cpp StreamUtilTest.cpp WavReaderTest.cpp)
add_executable(utest testmain.cpp ${testSources} ${sources})
add_executable(SnippetPublisher main.cpp ${sources})

find_package(Boost $ENV{BOOST_VERSION} COMPONENTS filesystem system)
target_link_libraries(utest ${Boost_LIBRARIES})
target_link_libraries(utest CppUTest)
target_link_libraries(utest CppUTestExt)
target_link_libraries(utest pthread)
target_link_libraries(utest rlogStub)

target_link_libraries(SnippetPublisher ${Boost_LIBRARIES})
target_link_libraries(SnippetPublisher pthread)
target_link_libraries(SnippetPublisher rlog)

