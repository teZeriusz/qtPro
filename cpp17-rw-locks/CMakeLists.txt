cmake_minimum_required(VERSION 3.5)

project(cpp17-rw-locks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(cpp17-rw-locks main.cpp)
target_link_libraries(cpp17-rw-locks ${CMAKE_THREAD_LIBS_INIT})
