cmake_minimum_required(VERSION 3.4)

project (opengl_learn C CXX)

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "Debug")
endif()

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/glad/include/"
)

add_subdirectory(glad)
add_subdirectory(triangle)

link_directories(
    "${PROJECT_BINARY_DIR}"
    )

link_libraries(
    triangle
)

add_executable(
    opengl_learn
    main.cc
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})