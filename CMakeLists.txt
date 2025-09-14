cmake_minimum_required(VERSION 3.16)
project(MyCrowAPI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Crow headers
include_directories(${CMAKE_SOURCE_DIR}/Crow-master/include)

# Asio headers (folder containing asio.hpp)
include_directories("C:/Users/yakup/CLionProjects/MyCrowAPI/asio-master/asio/include")

add_executable(MyCrowAPI main.cpp)

# Link pthread for MinGW/Unix
if (MINGW OR UNIX)
    target_link_libraries(MyCrowAPI pthread)
endif()

# On Windows, link Winsock libraries for Asio
if (WIN32)
    target_link_libraries(MyCrowAPI ws2_32 mswsock)
endif()
