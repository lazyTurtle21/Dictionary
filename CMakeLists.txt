cmake_minimum_required(VERSION 3.10)
project(dictionary)

set(CMAKE_CXX_STANDARD 14)
set(Boost_LIBRARY_DIR C:/msys64/mingw64/lib/)
set(Boost_INCLUDE_DIR C:/msys64/mingw64/include/)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system filesystem)


add_executable(dictionary src/main.cpp src/connection.cpp inc/connection.hpp src/reply.cpp inc/structs.hpp src/response.cpp inc/response.hpp src/request_parser.cpp inc/request_parser.hpp src/server.cpp inc/server.hpp src/parse_json_dictionary.cpp inc/parse_json_dictionary.h src/read_functions.cpp inc/read_functions.h)
target_link_libraries(dictionary Boost::system Threads::Threads Boost::filesystem)

if (WIN32)
    target_link_libraries(dictionary wsock32 ws2_32)
    target_link_libraries(dictionary wsock32 ws2_32)
endif ()