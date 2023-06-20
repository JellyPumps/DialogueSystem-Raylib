cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(dialogueSystem)

find_package(raylib 3.0 REQUIRED)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(dialogueSystem ${SOURCES})

target_include_directories(dialogueSystem PRIVATE includes)

target_link_libraries(dialogueSystem raylib)