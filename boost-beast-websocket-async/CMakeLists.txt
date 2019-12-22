cmake_minimum_required(VERSION 3.5)

project(boost-beast-websocket-async LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS system filesystem REQUIRED)

add_executable(boost-beast-websocket-async main.cpp)

target_link_libraries(boost-beast-websocket-async
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  pthread
)

## not listed in IDE
#add_custom_target(client_html ALL
##    SOURCES
#      client.html
#)

target_sources(${PROJECT_NAME} PRIVATE "client.html" "client.js")

#function(IndicateExternalFile _target)
#    foreach(_file IN ITEMS ${ARGN})
#        if ((IS_ABSOLUTE "${_file}" AND EXISTS "${_file}") OR
#            (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${_file}"))
#            target_sources(${_target} PRIVATE "${_file}")
#        endif()
#    endforeach()
#endfunction()

#file(WRITE "clien.xml" "")
#IndicateExternalFile(${PROJECT_NAME} "client.html")
