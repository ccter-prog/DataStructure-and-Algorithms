cmake_minimum_required(VERSION 3.28)
project(20-HeapSort)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(WARNING_FLAGS
	/W4
	/permissive-
	/w44456
	/w44457
	/w44244
	/w44388
	/w44389
)
add_compile_options(${WARNING_FLAGS})

add_library(heap_sort_templates INTERFACE)
target_include_directories(heap_sort_templates
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

string(REPLACE "-" "_" SAFE_TARGET_NAME ${PROJECT_NAME})
add_executable(${SAFE_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(${SAFE_TARGET_NAME} PRIVATE heap_sort_templates)