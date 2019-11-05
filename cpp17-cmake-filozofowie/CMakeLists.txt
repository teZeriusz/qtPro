cmake_minimum_required(VERSION 3.5)
project(cpp17-cmake-filozofowie LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

#set(CMAKE_BINARY_DIR, "build/")
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(build/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(cpp17-cmake-filozofowie main.cpp)
target_link_libraries(cpp17-cmake-filozofowie ${CONAN_LIBS} Threads::Threads)
