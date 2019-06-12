cmake_minimum_required(VERSION 3.10)
project(dictionary)

set(CMAKE_CXX_STANDARD 14)
set(Boost_LIBRARY_DIR C:/msys64/mingw64/lib/)
set(Boost_INCLUDE_DIR C:/msys64/mingw64/include/)
set(CMAKE_SOURCE_DIR src)

find_package(Boost REQUIRED COMPONENTS system)
include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_FILES ${CMAKE_SOURCE_DIR}/server.cpp ${CMAKE_SOURCE_DIR}/parse_json_dictionary.cpp inc/parse_json_dictionary.h src/http_headers.cpp inc/http_headers.hpp src/session.cpp inc/session.hpp)
add_executable(dictionary ${SOURCE_FILES})
target_link_libraries(dictionary Boost::system)

if(WIN32)
    target_link_libraries(dictionary wsock32 ws2_32)
    target_link_libraries(dictionary wsock32 ws2_32)
endif()