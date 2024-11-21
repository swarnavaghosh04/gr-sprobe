find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_SPROBE gnuradio-sprobe)

FIND_PATH(
    GR_SPROBE_INCLUDE_DIRS
    NAMES gnuradio/sprobe/api.h
    HINTS $ENV{SPROBE_DIR}/include
        ${PC_SPROBE_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_SPROBE_LIBRARIES
    NAMES gnuradio-sprobe
    HINTS $ENV{SPROBE_DIR}/lib
        ${PC_SPROBE_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-sprobeTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_SPROBE DEFAULT_MSG GR_SPROBE_LIBRARIES GR_SPROBE_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_SPROBE_LIBRARIES GR_SPROBE_INCLUDE_DIRS)
