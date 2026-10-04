cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "n_body")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

project(${PROJECT_NAME}
	VERSION 1.0
	LANGUAGES C
)

FetchContent_Declare(
	raylib
	GIT_REPOSITORY https://github.com/raysan5/raylib.git
	GIT_TAG 6.0
)

find_library(RAYLIB_LIB_PATH
	raylib
	PATHS "${CMAKE_SOURCE_DIR}/lib"
)
if(NOT RAYLIB_LIB_PATH)
	FetchContent_MakeAvailable(raylib)
endif()


file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.c")
add_executable(${PROJECT_NAME} ${SRC_FILES})

# directories
target_include_directories(${PROJECT_NAME}
	PUBLIC
	${CMAKE_SOURCE_DIR}/include
)
# default libs
file(GLOB LINK_FILES "${CMAKE_SOURCE_DIR}/lib/*.a")
target_link_libraries(${PROJECT_NAME}
	PRIVATE
	raylib
)
