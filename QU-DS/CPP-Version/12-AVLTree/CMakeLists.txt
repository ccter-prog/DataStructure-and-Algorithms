cmake_minimum_required(VERSION 3.15)
project(12-AVLTree)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(WARNING_FLAGS
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wsign-conversion
    -fno-common
)
add_compile_options(${WARNING_FLAGS})
add_library(tree_templates INTERFACE)
target_include_directories(tree_templates
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE tree_templates)