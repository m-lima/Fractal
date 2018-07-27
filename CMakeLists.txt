cmake_minimum_required(VERSION 3.2)
project(Fractal CXX)

##------------------------------------------------------------------------------
## Initialization
##

include("${CMAKE_SOURCE_DIR}/Init.cmake")

##------------------------------------------------------------------------------
## Dependencies
##

# MFL
include("${EXT_DIR}/mfl/mfl.cmake")
list(APPEND LIBRARIES mfl)

# QT
include("${EXT_DIR}/qt/qt.cmake")
list(APPEND LIBRARIES qt)

## QT
#if (MSVC)
#  # GOTTA FIX THIS!! CMake keeps pointing to 32bit version of QT
#  # and this was the only way I found to force a 64bit linkage
#  set (CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.7.0\\5.7\\msvc2015_64\\")
#elseif(APPLE)
#  set (CMAKE_PREFIX_PATH "~/Qt/5.7/clang_64")
#endif()
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#find_package(Qt5Widgets)

##------------------------------------------------------------------------------
## Sources
##

set(SOURCES
  ${SRC_DIR}/cpp/main.cpp
  ${SRC_DIR}/cpp/main_window.cpp
  ${SRC_DIR}/cpp/main_window.hpp
  ${SRC_DIR}/cpp/fractal_widget.cpp
  ${SRC_DIR}/cpp/fractal_widget.hpp
  ${SRC_DIR}/cpp/shader.cpp
  ${SRC_DIR}/cpp/shader.hpp
  )

set(OPENGL_SRC
  ${OPENGL_SRC_DIR}/fractal.vs
  ${OPENGL_SRC_DIR}/fractal.fs
  )

if(MSVC)
  list(APPEND SOURCES ${OPENGL_SRC})
endif()

##------------------------------------------------------------------------------
## Targets
##

add_executable(fractal ${SOURCES})
target_link_libraries(fractal PRIVATE mfl qt)
#set_target_properties(fractal PROPERTIES CXX_LANGUAGE_STANDARD 11)
#target_link_libraries(fractal ${LIBRARIES})
#target_link_libraries(fractal Qt5::Widgets)
#target_include_directories(fractal PRIVATE ${INCLUDE_DIRS})
#set_target_properties(fractal PROPERTIES CXX_LANGUAGE_STANDARD 11)
#add_dependencies(fractal always)

##------------------------------------------------------------------------------
## MSVC Specifics
##

#if(WIN32)
#  set_target_properties(fractal PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
#  set_target_properties(fractal PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
#
#  if(MSVC)
#	source_group("OpenGL" FILES ${OPENGL_SRC})
#
#	if(${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 3.5)
#	  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT fractal)
#	endif()
#  endif()
#endif()
