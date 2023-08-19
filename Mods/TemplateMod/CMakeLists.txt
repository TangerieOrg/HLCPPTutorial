cmake_minimum_required(VERSION 3.18)

set(TARGET TemplateMod)
project(${TARGET})

FILE(GLOB_RECURSE ${TARGET}_HEADERS "src/*.hpp")
FILE(GLOB_RECURSE ${TARGET}_SOURCES "src/*.cpp")

add_library(${TARGET} SHARED ${${TARGET}_HEADERS} ${${TARGET}_SOURCES})

# Makes the dlls output as main.dll to Output/Mods/<ModName>/main.dll
set_target_properties(
	${TARGET} PROPERTIES 
	OUTPUT_NAME main
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Output/Mods/${TARGET}
)

target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${TARGET} PUBLIC ue4ss)