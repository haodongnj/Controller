cmake_minimum_required(VERSION 3.10)

project(controller LANGUAGES CXX C)

#SET(CMAKE_CXX_STANDARD 11)

add_library(controller STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/filter.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/forc.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pi.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/pr.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/pwrc.c
#        ${CMAKE_CURRENT_SOURCE_DIR}/src/rc.c
        )

target_include_directories(controller PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)