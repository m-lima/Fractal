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

add_subdirectory(fmt)
list(APPEND INCLUDE_DIRS fmt)
list(APPEND LIBRARIES fmt)

# QT
if (MSVC)
  # GOTTA FIX THIS!! CMake keeps pointing to 32bit version of QT
  # and this was the only way I found to force a 64bit linkage
  set (CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.7.0\\5.7\\msvc2015_64\\")
elseif(APPLE)
  set (CMAKE_PREFIX_PATH "~/Qt/5.7/clang_64")
endif()
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
find_package(Qt5Widgets)

##------------------------------------------------------------------------------
## Sources
##

set(SOURCES
  ${CPP_SRC_DIR}/main.cpp
  ${CPP_SRC_DIR}/mainWindow.cpp
  ${CPP_SRC_DIR}/mainWindow.hpp
  ${CPP_SRC_DIR}/fractalWidget.cpp
  ${CPP_SRC_DIR}/fractalWidget.hpp
  ${CPP_SRC_DIR}/shader.cpp
  ${CPP_SRC_DIR}/shader.hpp
  )

set(OPENGL_SRC
  ${OPENGL_SRC_DIR}/fractal.vs
  ${OPENGL_SRC_DIR}/fractal.fs
  )

if(MSVC)
  list(APPEND SOURCES ${OPENGL_SRC})
endif()

##------------------------------------------------------------------------------
## Copies
##

add_custom_target(always ALL DEPENDS copy_extra_sources)
add_custom_command(
  OUTPUT copy_extra_sources
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/opengl
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/${OPENGL_SRC_DIR} ${CMAKE_BINARY_DIR}/opengl
  DEPENDS always_execute
  )
add_custom_command(OUTPUT always_execute COMMAND ${CMAKE_COMMAND} -E echo)

##------------------------------------------------------------------------------
## Targets
##

add_executable(fractal ${SOURCES})
set_target_properties(fractal PROPERTIES CXX_LANGUAGE_STANDARD 11)
target_link_libraries(fractal ${LIBRARIES})
target_link_libraries(fractal Qt5::Widgets)
target_include_directories(fractal PRIVATE ${INCLUDE_DIRS})
set_target_properties(fractal PROPERTIES CXX_LANGUAGE_STANDARD 11)
add_dependencies(fractal always)

##------------------------------------------------------------------------------
## MSVC Specifics
##

if(WIN32)
  set_target_properties(fractal PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
  set_target_properties(fractal PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")

  if(MSVC)
	source_group("OpenGL" FILES ${OPENGL_SRC})

	if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.5)
	  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT fractal)
	endif()
  endif()
endif()
