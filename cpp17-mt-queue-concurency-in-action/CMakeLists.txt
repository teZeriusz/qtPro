cmake_minimum_required(VERSION 3.5)

project(cpp17-mt-queue-concurency-in-action LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
#find_package(tbb REQUIRED)


add_executable(cpp17-mt-queue-concurency-in-action main.cpp)
target_link_libraries(cpp17-mt-queue-concurency-in-action ${CMAKE_THREAD_LIBS_INIT} -ltbb)
