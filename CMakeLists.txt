cmake_minimum_required(VERSION 3.10)
project(dictionary)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_SOURCE_DIR src)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/server.cpp ${CMAKE_SOURCE_DIR}/parse_json_dictionary.cpp  src/http_headers.cpp inc/http_headers.hpp src/session.cpp inc/session.hpp)
add_executable(dictionary ${SOURCE_FILES})
target_link_libraries(dictionary Boost::system Threads::Threads)

if(WIN32)
    target_link_libraries(dictionary wsock32 ws2_32)
    target_link_libraries(dictionary wsock32 ws2_32)
endif()