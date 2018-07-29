configure_file("${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt.in" "${CMAKE_BINARY_DIR}/deps/nano/CMakeLists.txt")
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/deps/nano")
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/deps/nano")

set(NANOGUI_BUILD_EXAMPLE OFF CACHE BOOL " " FORCE)
set(NANOGUI_BUILD_PYTHON OFF CACHE BOOL " " FORCE)
set(NANOGUI_BUILD_SHARED OFF CACHE BOOL " " FORCE)
#set(NANOGUI_USE_GLAD OFF CACHE BOOL " " FORCE)
set(NANOGUI_INSTALL OFF CACHE BOOL " " FORCE)

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/pack/nano")

add_library(nano INTERFACE)
target_include_directories(nano INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/pack/nano/include"
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/pack/nano/include>
    $<INSTALL_INTERFACE:include>)
target_include_directories(nano INTERFACE
    "${NANOGUI_EXTRA_INCS}"
    $<BUILD_INTERFACE:${NANOGUI_EXTRA_INCS}>
    $<INSTALL_INTERFACE:${NANOGUI_EXTRA_INCS}>)
target_link_libraries(nano INTERFACE nanogui "${NANOGUI_EXTRA_LIBS}")
