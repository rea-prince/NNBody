cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "n_body")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(${PROJECT_NAME}
	VERSION 1.0
	LANGUAGES C
)

file(GLOB SRC_FILES
	"${CMAKE_SOURCE_DIR}/src/*.c"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME}
	PUBLIC
	${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
	${CMAKE_SOURCE_DIR}/lib/libraylib.a
)

if (WIN32)
	target_link_libraries(${PROJECT_NAME}
		PRIVATE
		winmm
	)
elseif (UNIX AND NOT APPLE)
	target_link_libraries(${PROJECT_NAME}
		PRIVATE
		m
		dl
		pthread
		GL
		X11
	)
elseif (APPLE)
	target_link_libraries(${PROJECT_NAME}
		PRIVATE
		"-framework Cocoa"
		"-framework IOKit"
		"-framework OpenGL"
	)
endif()
