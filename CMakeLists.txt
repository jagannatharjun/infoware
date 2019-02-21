project(infoware CXX)
cmake_minimum_required(VERSION 3.12)

option(INFOWARE_USE_OPENCL "Use OpenCl for gpu Detection" OFF)
option(INFOWARE_USE_X11  "Use X11 for gpu Detection" OFF)
option(INFOWARE_USE_D3D "Use D3d for gpu Detection" ON)
option(INFOWARE_USE_OPENGL "Use OpenGL for gpu Detection" OFF)

file(GLOB_RECURSE SRCS src/*)
add_library(infoware STATIC ${SRCS})
target_include_directories(infoware PUBLIC include/)
set_property(TARGET infoware PROPERTY CXX_STANDARD 14)

if (CMAKE_COMPILER_IS_GNUCXX) 
	SET(GCC_COVERAGE_COMPILE_FLAGS "-march=native")
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
endif()

if (CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(infoware gdi32 version Ole32 OleAut32 wbemuuid)

	if (INFOWARE_USE_OPENCL)
		find_package(OPENCL)
		if (OPENCL_FOUND)
			target_link_libraries(infoware ${OPENCL_LIBRARIES})
			target_compile_definitions(infoware PUBLIC INFOWARE_USE_OPENCL)
		endif()
	endif()
	
	if (INFOWARE_USE_X11)
			target_link_libraries(infoware X11)
			target_compile_definitions(infoware PUBLIC INFOWARE_USE_X11)
	endif()
	
	if (INFOWARE_USE_D3D)
		target_link_libraries(infoware dxgi)
		target_compile_definitions(infoware PUBLIC INFOWARE_USE_D3D)
	endif()
	
	if (INFOWARE_USE_OPENGL)
		find_package(OPENGL)
		if (OPENGL_Found)
			target_link_libraries(infoware ${OPENGL_LIBRARIES})
			target_compile_definitions(infoware PUBLIC INFOWARE_USE_OPENGL)
		endif()
	endif()
	
endif()


add_executable(infoware_example_cpu examples/cpu.cpp)
target_link_libraries(infoware_example_cpu infoware)

add_executable(infoware_example_gpu examples/gpu.cpp)
target_link_libraries(infoware_example_gpu infoware)

add_executable(infoware_example_system examples/system.cpp)
target_link_libraries(infoware_example_system infoware)