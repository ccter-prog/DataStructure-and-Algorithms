cmake_minimum_required(VERSION 3.25)
project(23-BucketSort)

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

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(PROJECT_CONFIG_NAME
		"win-msvc-x64-debug"
	)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
	set(PROJECT_CONFIG_NAME
		"win-msvc-x64-release"
	)
else()
	set(PROJECT_CONFIG_NAME
		"unknown"
	)
endif()

set(OUTPUT_ROOT
	"${CMAKE_SOURCE_DIR}/out"
)
set(BIN_OUTPUT_DIR
	"${OUTPUT_ROOT}/bin/${PROJECT_CONFIG_NAME}"
)

add_library(bucket_sort INTERFACE)

string(REPLACE "-" "_" SAFE_TARGET_NAME ${PROJECT_NAME})
add_executable(${SAFE_TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_include_directories(bucket_sort
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(${SAFE_TARGET_NAME} PRIVATE bucket_sort)

set_target_properties(${SAFE_TARGET_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY
		"${BIN_OUTPUT_DIR}"
)