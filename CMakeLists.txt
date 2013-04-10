project(SnippetPublisher)
cmake_minimum_required(VERSION 2.6)

include_directories($ENV{BOOST_ROOT}/ $ENV{RLOG_HOME} $ENV{CPPUTEST_HOME}/include)
# START_HIGHLIGHT
link_directories($ENV{RLOG_HOME}/rlog/.libs 
   ${RLOG_BINARY_DIR}/rlog 
   $ENV{CPPUTEST_HOME}/lib)
# END_HIGHLIGHT

# START_HIGHLIGHT
add_subdirectory(rlog)
# END_HIGHLIGHT

add_definitions(-std=c++0x)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -DRLOG_COMPONENT=debug -Wall")
set(sources WavReader.cpp WavDescriptor.cpp)
set(testSources WavReaderTest.cpp)
add_executable(utest testmain.cpp ${testSources} ${sources})
add_executable(SnippetPublisher main.cpp ${sources})

find_package(Boost $ENV{BOOST_VERSION} COMPONENTS filesystem system)
target_link_libraries(utest ${Boost_LIBRARIES})
target_link_libraries(utest CppUTest)
target_link_libraries(utest pthread)
# START_HIGHLIGHT
target_link_libraries(utest rlogStub)
# END_HIGHLIGHT

target_link_libraries(SnippetPublisher ${Boost_LIBRARIES})
target_link_libraries(SnippetPublisher pthread)
target_link_libraries(SnippetPublisher rlog)

