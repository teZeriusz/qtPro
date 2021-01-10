cmake_minimum_required(VERSION 3.13)
project(appka)
set(CMAKE_CXX_STANDARD 20)

add_executable(appka main.cpp)


project(Test_appka)
enable_testing()

find_package(PkgConfig REQUIRED)
pkg_check_modules(gtest REQUIRED gtest>=1.8.1)

SET(CMAKE_CXX_FLAGS -pthread)

include_directories(${gtest_INCLUDE_DIRS})

add_executable(Test_appka main_test.cpp)
target_link_libraries(Test_appka ${gtest_LIBRARIES})

