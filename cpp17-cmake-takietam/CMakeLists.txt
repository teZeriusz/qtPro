cmake_minimum_required(VERSION 3.5)

project(cpp17-cmake-takietam LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpp17-cmake-takietam main.cpp)
target_link_libraries(cpp17-cmake-takietam
    pthread)
