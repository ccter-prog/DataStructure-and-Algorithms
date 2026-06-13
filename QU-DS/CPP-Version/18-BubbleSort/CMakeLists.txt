cmake_minimum_required(VERSION 3.15)
project(18-BubbleSort)

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

add_library(bubble_sort_templates INTERFACE)
target_include_directories(bubble_sort_templates
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(main PRIVATE bubble_sort_templates)