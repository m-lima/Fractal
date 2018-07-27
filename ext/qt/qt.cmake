include(ExternalProject)
include(GNUInstallDirs)

#if (WIN32)
#  set(QT_PROJECT_URL "http://download.qt.io/official_releases/qt/5.11/5.11.1/single/qt-everywhere-src-5.11.1.zip")
#  set(QT_PROJECT_HASH "SHA256=7e439f4a1786abc5a6040047f7e6e0e963c5a3516c1169141e99febb187d3832")
#else()
  set(QT_PROJECT_URL "http://download.qt.io/official_releases/qt/5.11/5.11.1/single/qt-everywhere-src-5.11.1.tar.xz")
  set(QT_PROJECT_HASH "SHA256=39602cb08f9c96867910c375d783eed00fc4a244bffaa93b801225d17950fb2b")
#endif()

ExternalProject_Add(qt-project
  PREFIX deps/qt
  URL ${QT_PROJECT_URL}
  URL_HASH ${QT_PROJECT_HASH}
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/qt
  STAMP_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/tmp/qt
  TMP_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/tmp/qt
  CONFIGURE_COMMAND ""
  INSTALL_COMMAND ""
  )

add_library(qt INTERFACE)

#target_compile_definitions(mfl INTERFACE FMT_HEADER_ONLY=1)
#
#target_include_directories(mfl INTERFACE
#  ${CMAKE_CURRENT_LIST_DIR}/pack/mfl/include
#  $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/pack/mfl/ext/fmt/pack/fmt/include>
#  $<INSTALL_INTERFACE:include>)

add_dependencies(qt qt-project)

