cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(dialogueSystem)

find_package(raylib 3.0 REQUIRED)
find_package(nlohmann_json 3.11.2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")

add_executable(dialogueSystem ${SOURCES})

target_include_directories(dialogueSystem PRIVATE includes)

target_link_libraries(dialogueSystem raylib)
target_link_libraries(dialogueSystem nlohmann_json::nlohmann_json)