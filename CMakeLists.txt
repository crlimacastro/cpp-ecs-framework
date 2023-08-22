cmake_minimum_required(VERSION 3.13)

project(fae_framework VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME})

add_subdirectory(external/STX)
add_subdirectory(external/glm)
add_subdirectory(external/entt)
add_subdirectory(external/glfw)
add_subdirectory(external/gl3w)
add_subdirectory(external/assimp)
add_subdirectory(external/reactphysics3d)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
# 		"external/stx/include"
# 		"external/glm/glm"
# 		"external/entt/src/entt"
# 		"external/glfw/include"
# 		"external/assimp/include"
# 		"external/reactphysics3d/include"
)

# target_link_libraries(${PROJECT_NAME}
# 	PUBLIC
# 		stx
# 		glm
# 		EnTT
# 		glfw
# 		assimp
# 		reactphysics3d
# 	PRIVATE
# )

# target_link_directories(${PROJECT_NAME} PUBLIC
# 	"external/stx/src"
# 	"external/glm/glm"
# 	"external/entt/src/entt"
# 	"external/glfw/src"
# 	"external/reactphysics3d/src"
# )

# configure_file(cmake/fae_framework_config.h.in fae_framework.h)

# target_compile_definitions(${PROJECT_NAME} PUBLIC RESOURCES_PATH=${CMAKE_CURRENT_SOURCE_DIR}/resources)
# target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
# file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
# target_sources(${PROJECT_NAME} PRIVATE ${SRCS})