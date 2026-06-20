cmake_minimum_required(VERSION 3.15)
project(test)

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

add_library(shell_sort_templates INTERFACE)
target_include_directories(shell_sort_templates
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_executable(main ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(main PRIVATE shell_sort_templates)