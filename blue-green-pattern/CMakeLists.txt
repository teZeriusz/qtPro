cmake_minimum_required(VERSION 3.13)
project(blue-green-pattern)
set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)


#project(Test_${PROJECT_NAME})
enable_testing()

find_package(PkgConfig REQUIRED)
pkg_check_modules(gtest REQUIRED gtest>=1.8.1)

SET(CMAKE_CXX_FLAGS -pthread)

include_directories(${gtest_INCLUDE_DIRS})

add_executable(Test_${PROJECT_NAME} main_test.cpp)
target_link_libraries(Test_${PROJECT_NAME} ${gtest_LIBRARIES})

