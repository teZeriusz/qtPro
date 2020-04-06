cmake_minimum_required(VERSION 3.5)

project(nokia-etteplan-zagadnienia LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(Threads REQUIRED)

add_executable(nokia-etteplan-zagadnienia main.cpp)
target_link_libraries(nokia-etteplan-zagadnienia ${CMAKE_THREAD_LIBS_INIT} -ltbb)
