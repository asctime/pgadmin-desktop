# Optional MinGW cross toolchain. A native build does not use this file.
# Set the environment before configuring:
#   MINGW_ROOT   compiler prefix directory
#   WXWIN        wxWidgets 3.2 tree, if wx-config is not on PATH

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

if(NOT DEFINED ENV{MINGW_ROOT})
    message(FATAL_ERROR "MINGW_ROOT is required for this toolchain file")
endif()

set(CMAKE_C_COMPILER "$ENV{MINGW_ROOT}/bin/x86_64-w64-mingw32-gcc")
set(CMAKE_CXX_COMPILER "$ENV{MINGW_ROOT}/bin/x86_64-w64-mingw32-g++")
set(CMAKE_RC_COMPILER "$ENV{MINGW_ROOT}/bin/x86_64-w64-mingw32-windres")

set(CMAKE_FIND_ROOT_PATH "$ENV{MINGW_ROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
