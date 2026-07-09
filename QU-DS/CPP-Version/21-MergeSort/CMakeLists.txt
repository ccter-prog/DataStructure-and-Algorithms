cmake_minimum_required(VERSION 3.15)
project(21-MergeSort)

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

add_library(merge_sort_templates INTERFACE)
target_include_directories(merge_sort_templates
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

string(REPLACE "-" "_" SAFE_TARGET_NAME ${PROJECT_NAME})
add_executable(${SAFE_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${SAFE_TARGET_NAME} PRIVATE merge_sort_templates)