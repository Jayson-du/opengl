set (CURRENT_PROJECT_NAME triangle)

link_directories(
    "/usr/lib/x86_64-linux-gnu/"
    "/snap/gnome-42-2204/68/usr/lib/x86_64-linux-gnu/"
    "${PROJECT_BINARY_DIR}"
    )

link_libraries(
    glad
    GL
    glut
    glfw
    dl
)

add_library(triangle
            triangle.cc
            )

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})