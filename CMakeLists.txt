cmake_minimum_required(VERSION 3.13)

project(fae_framework VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_TOOLCHAIN_FILE ./vcpkg/scripts/buildsystems/vcpkg.cmake)

add_subdirectory(external)

file(GLOB_RECURSE SRCS "src/*.cpp")
add_library(${PROJECT_NAME} ${SRCS})

add_custom_target(${PROJECT_NAME}_copy_resources ALL
	COMMAND ${CMAKE_COMMAND} -E
	copy_directory "${PROJECT_SOURCE_DIR}/resources" "${PROJECT_BINARY_DIR}/resources"
	COMMENT "Copying ${PROJECT_SOURCE_DIR}/resources to ${PROJECT_BINARY_DIR}/resources"
)

add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}_copy_resources)


target_precompile_headers(${PROJECT_NAME}
	PUBLIC
		"src/fae_pch.hpp"
	PRIVATE
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
		stx
		entt
		raylib
		raylib_cpp
		reactphysics3d
	PRIVATE
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		stx
		EnTT
		raylib
		raylib_cpp
		reactphysics3d
	PRIVATE
)