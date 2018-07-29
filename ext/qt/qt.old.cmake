include(ExternalProject)
include(GNUInstallDirs)

#if (WIN32)
#  set(QT_PROJECT_URL "http://download.qt.io/official_releases/qt/5.11/5.11.1/single/qt-everywhere-src-5.11.1.zip")
#  set(QT_PROJECT_HASH "SHA256=7e439f4a1786abc5a6040047f7e6e0e963c5a3516c1169141e99febb187d3832")
#else()
#  set(QT_PROJECT_URL "http://download.qt.io/official_releases/qt/5.11/5.11.1/single/qt-everywhere-src-5.11.1.tar.xz")
#  set(QT_PROJECT_HASH "SHA256=39602cb08f9c96867910c375d783eed00fc4a244bffaa93b801225d17950fb2b")
#endif()

set(QT_PROJECT_URL "https://download.qt.io/official_releases/qt/5.11/5.11.1/submodules/qtbase-everywhere-src-5.11.1.tar.xz")
set(QT_PROJECT_HASH "SHA256=a0d047b2da5782c8332c59ae203984b64e4d5dc5f4ba9c0884fdbe753d0afb46")

#GIT_REPOSITORY "https://code.qt.io/cgit/qt/qtbase.git"
#GIT_TAG "5.11.1"
ExternalProject_Add(qt-project
  PREFIX deps/qt
  URL ${QT_PROJECT_URL}
  URL_HASH ${QT_PROJECT_HASH}
  DOWNLOAD_DIR "${CMAKE_CURRENT_LIST_DIR}/pack/down"
  SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}/pack/qt"
  STAMP_DIR "${CMAKE_CURRENT_LIST_DIR}/pack/tmp/qt"
  TMP_DIR "${CMAKE_CURRENT_LIST_DIR}/pack/tmp/qt"
  BUILD_IN_SOURCE 1
  CONFIGURE_COMMAND "./configure"
    -prefix "qt"
    -extprefix "${CMAKE_CURRENT_LIST_DIR}/pack/install"
    -opensource
    -confirm-license
    -release
    -nomake examples
    -nomake tests
    -nomake tools
    -no-feature-concurrent
    -no-feature-dbus
    -no-feature-network
    -no-feature-sql
    -no-feature-testlib
    -no-feature-xml
  BUILD_COMMAND make
  INSTALL_COMMAND make install
  )

#-static

#-qt-zlib
#-qt-pcre
#-qt-libpng
#-qt-libjpeg
#-qt-freetype

#-skip qt3d
#-skip qtactiveqt
#-skip qtandroidextras
#-skip qtcanvas3d
#-skip qtcharts
#-skip qtconnectivity
#-skip qtdatavis3d
#-skip qtdeclarative
#-skip qtdoc
#-skip qtgamepad
#-skip qtgraphicaleffects
#-skip qtimageformats
#-skip qtlocation
#-skip qtmacextras
#-skip qtmultimedia
#-skip qtnetworkauth
#-skip qtpurchasing
#-skip qtquickcontrols
#-skip qtquickcontrols2
#-skip qtremoteobjects
#-skip qtscript
#-skip qtscxml
#-skip qtsensors
#-skip qtserialbus
#-skip qtserialport
#-skip qtspeech
#-skip qtsvg
#-skip qttools
#-skip qttranslations
#-skip qtvirtualkeyboard
#-skip qtwayland
#-skip qtwebchannel
#-skip qtwebengine
#-skip qtwebglplugin
#-skip qtwebsockets
#-skip qtwebview
#-skip qtwinextras
#-skip qtx11extras
#-skip qtxmlpatterns

add_library(qt INTERFACE)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(Qt5_DIR ${CMAKE_CURRENT_LIST_DIR}/pack/install/lib/cmake/Qt5)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(qt INTERFACE Qt5::Widgets)

add_dependencies(qt qt-project)





configure_file("${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt.in" "${CMAKE_BINARY_DIR}/deps/qt/CMakeLists.txt")
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/deps/qt")
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/deps/qt")

