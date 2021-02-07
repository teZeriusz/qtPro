cmake_minimum_required(VERSION 3.13)
project(appka)
set(CMAKE_CXX_STANDARD 20)
set(THREADS_PREFER_PTHREAD_FLAG ON)
add_executable(appka main.cpp)
find_package(Threads REQUIRED)

project(Test_appka)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)
target_link_libraries(appka CONAN_PKG::range-v3 ${CMAKE_THREAD_LIBS_INIT})

enable_testing()


find_package(PkgConfig REQUIRED)
pkg_check_modules(gtest REQUIRED gtest>=1.8.1)

SET(CMAKE_CXX_FLAGS -pthread)
include_directories(${gtest_INCLUDE_DIRS})
add_executable(Test_appka main_test.cpp)
target_link_libraries(Test_appka ${gtest_LIBRARIES} CONAN_PKG::range-v3 ${CMAKE_THREAD_LIBS_INIT})

