cmake_minimum_required(VERSION 3.18)

set(TARGET ModUtils)
project(${TARGET})

FILE(GLOB_RECURSE ${TARGET}_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/ModUtils/*.hpp")
FILE(GLOB_RECURSE ${TARGET}_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ModUtils/*.cpp")

add_library(${TARGET} STATIC ${${TARGET}_HEADERS} ${${TARGET}_SOURCES})

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${TARGET} PUBLIC ue4ss)