cmake_minimum_required(VERSION 3.5)

project(cpp20-barrier LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(cpp20-barrier main.cpp)
target_link_libraries(cpp20-barrier ${CMAKE_THREAD_LIBS_INIT})
