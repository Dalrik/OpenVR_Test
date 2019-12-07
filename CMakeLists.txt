# CMakeList.txt : CMake project for OpenVR_Test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("OpenVR_Test")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(SDL2 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(OpenVR REQUIRED)

set(EXTRA_RESOURCES "resources/hellovr_actions.json"
	                "resources/hellovr_bindings_generic.json"
					"resources/hellovr_bindings_vive_controller.json"
					"resources/cube_texture.png")

# Add source to this project's executable.
add_executable (OpenVR_Test
	            "OpenVR_Test.cpp" "OpenVR_Test.h"
				"shared/compat.h"
				"shared/lodepng.cpp" "shared/lodepng.h"
				"shared/Matrices.cpp" "shared/Matrices.h"
				"shared/pathtools.cpp" "shared/pathtools.h"
				"shared/strtools.cpp" "shared/strtools.h"
				"shared/Vectors.h")
target_link_libraries(OpenVR_Test PRIVATE SDL2::SDL2 SDL2::SDL2main GLEW::GLEW OpenVR::OpenVR)

if (NOT CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_CURRENT_BINARY_DIR)
	set(OUT_RESOURCE_FILES "")
	foreach(item IN LISTS EXTRA_RESOURCES)
		message(STATUS ${item})
		add_custom_command(
			OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${item}"
			COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${item}" "${CMAKE_CURRENT_BINARY_DIR}/${item}"
			DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${item}"
	    )
		list(APPEND OUT_RESOURCE_FILES "${CMAKE_CURRENT_BINARY_DIR}/${item}")
	endforeach()
	add_custom_target(resources ALL DEPENDS ${OUT_RESOURCE_FILES})
	add_dependencies(OpenVR_Test resources)
endif()

# TODO: Add tests and install targets if needed.
