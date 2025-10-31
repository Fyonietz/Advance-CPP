CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

project(dynamic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE MAIN "main.cpp")
add_subdirectory(libs)

add_executable(${PROJECT_NAME} ${MAIN})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs)


