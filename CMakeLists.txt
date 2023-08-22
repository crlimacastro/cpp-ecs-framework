cmake_minimum_required(VERSION 3.13)

project(fae_framework VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/STX)
add_subdirectory(external/glm)
add_subdirectory(external/entt)
add_subdirectory(external/glfw)
add_subdirectory(external/assimp)
add_subdirectory(external/reactphysics3d)

file(GLOB_RECURSE SRCS "src/*.cpp")
add_library(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		stx
		glm
		assimp
		glfw
	PRIVATE
		entt
		reactphysics3d
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		stx
 		glm
		assimp
		glfw
 	PRIVATE
		EnTT
		reactphysics3d
)

# configure_file(cmake/fae_framework_config.h.in fae_framework.h)

# target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH=${CMAKE_CURRENT_SOURCE_DIR}/resources)