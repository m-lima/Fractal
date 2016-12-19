cmake_minimum_required(VERSION 3.2)
project(Fractal CXX)

# Handle Mac's Clang
if(APPLE)
  set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
endif()

STRING(REGEX REPLACE "\\\\" "/" ENV_HOME_DIR $ENV{HOME})

# Add custom modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/findcmake")
set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_PREFIX_PATH "${ENV_HOME_DIR}/Lib")

# Set base directories
set(CPP_SRC_DIR "src/cpp")
set(OPENGL_SRC_DIR "src/opengl")
set(OPENCL_SRC_DIR "src/opencl")

# Add manual libs
list (APPEND INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/lib/include")

##------------------------------------------------------------------------------
## Dependencies
##

find_package(OpenGL REQUIRED)
list(APPEND INCLUDE_DIRS ${OPENGL_INCLUDE_DIRS})
list(APPEND LIBRARIES ${OPENGL_LIBRARIES})
message(STATUS "OpenGL Include: " "${OPENGL_INCLUDE_DIRS}")
message(STATUS "OpenGL Libraries: " "${OPENGL_LIBRARIES}")

find_package(OPENCL REQUIRED)
list(APPEND INCLUDE_DIRS ${OpenCL_INCLUDE_DIR})
list(APPEND LIBRARIES ${OpenCL_LIBRARIES})
message(STATUS "OpenCL Include: " "${OpenCL_INCLUDE_DIR}")
message(STATUS "OpenCL Libraries: " "${OpenCL_LIBRARIES}")

# SDL2
# set(SDL_INCLUDE_DIR "${ENV_HOME_DIR}/Lib/SDL2/SDL2-2.0.5")
find_package(SDL2 REQUIRED)
list(APPEND INCLUDE_DIRS ${SDL2_INCLUDE_DIRS})
list(APPEND LIBRARIES ${SDL2_LIBRARY})
message(STATUS "SDL2 Include: " "${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2 Libraries: " "${SDL2_LIBRARIES}")

add_subdirectory(fmt)
list(APPEND INCLUDE_DIRS fmt)
list(APPEND LIBRARIES fmt)

# TBB
# set(ENV{TBB_ARCH_PLATFORM} "intel64/vc14")
# set(TBB_ROOT_DIR "${ENV_HOME_DIR}/Lib/TBB")

# find_package(TBB REQUIRED)
# list(APPEND INCLUDE_DIRS ${TBB_INCLUDE_DIRS})
# list(APPEND LIBRARIES ${TBB_LIBRARIES})
# message(STATUS "TBB Include: " "${TBB_INCLUDE_DIRS}")
# message(STATUS "TBB Libraries: " "${TBB_LIBRARIES}")

##------------------------------------------------------------------------------
## LAS
##
# list (APPEND LIBRARIES "${CMAKE_SOURCE_DIR}/lib/bin/LASlib.lib")
# list (APPEND LIBRARIES "${CMAKE_SOURCE_DIR}/lib/bin/LASzip.dll")

##------------------------------------------------------------------------------
## Sources
##

set(SOURCES
  ${CPP_SRC_DIR}/main.cpp
  ${CPP_SRC_DIR}/renderer.cpp
  ${CPP_SRC_DIR}/renderer.hpp
  )

set(OPENGL_SRC
  ${OPENGL_SRC_DIR}/fractal.vs
  ${OPENGL_SRC_DIR}/fractal.fs
  )

set(OPENCL_SRC
  ${OPENCL_SRC_DIR}/fractal.cl
  )

if(MSVC)
  list(APPEND SOURCES ${OPENGL_SRC})
  list(APPEND SOURCES ${OPENCL_SRC})
endif()

##------------------------------------------------------------------------------
## Copies
##

add_custom_target(always ALL DEPENDS copy_opencl_sources)
add_custom_command(
  OUTPUT copy_opencl_sources
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/opengl
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/opencl
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${OPENGL_SRC_DIR} ${CMAKE_BINARY_DIR}/opengl
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${OPENCL_SRC_DIR} ${CMAKE_BINARY_DIR}/opencl
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/lib/bin ${CMAKE_BINARY_DIR}
  DEPENDS always_execute
  )
add_custom_command(OUTPUT always_execute COMMAND ${CMAKE_COMMAND} -E echo)

##------------------------------------------------------------------------------
## Targets
##

add_executable(fractal ${SOURCES})
set_target_properties(fractal PROPERTIES CXX_LANGUAGE_STANDARD 11)
target_link_libraries(fractal ${LIBRARIES})
target_include_directories(fractal PRIVATE ${INCLUDE_DIRS})
set_target_properties(fractal PROPERTIES CXX_LANGUAGE_STANDARD 11)
add_dependencies(fractal always)

##------------------------------------------------------------------------------
## MSVC Specifics
##

if(MSVC)
  source_group("OpenGL" FILES ${OPENGL_SRC})
  source_group("OpenCL" FILES ${OPENCL_SRC})

  if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.5)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT fractal)
  endif()
endif()
