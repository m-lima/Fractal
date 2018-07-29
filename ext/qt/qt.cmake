configure_file("${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt.in" "${CMAKE_BINARY_DIR}/deps/qt/CMakeLists.txt")
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/deps/qt")
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/deps/qt")

set(Qt5_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/install/lib/cmake/Qt5)
