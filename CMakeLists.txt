cmake_minimum_required(VERSION 3.16)
project(pgadmin VERSION 4.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(wxWidgets 3.2 REQUIRED COMPONENTS stc aui xrc html xml adv core base net)
include(${wxWidgets_USE_FILE})

# WinMain only for the MSW toolkit. GTK, Motif, X11, macOS and the rest use main().
set(PGADMIN_SUBSYSTEM "")
if(APPLE)
    set(PGADMIN_SUBSYSTEM MACOSX_BUNDLE)
elseif(WIN32 AND (NOT wxWidgets_DEFINITIONS OR wxWidgets_DEFINITIONS MATCHES "__WXMSW__"))
    set(PGADMIN_SUBSYSTEM WIN32)
endif()

find_package(PostgreSQL REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(LibXslt REQUIRED)

file(GLOB_RECURSE PGADMIN_SOURCES CONFIGURE_DEPENDS
    agent/*.c*
    ctl/*.c*
    db/*.c*
    dd/*.c*
    debugger/*.c*
    dlg/*.c*
    frm/*.c*
    gqb/*.c*
    hotdraw/*.c*
    ogl/*.c*
    pgscript/*.c*
    Postgres/*.c*
    pro_scheduler/*.c*
    schema/*.c*
    slony/*.c*
    utils/*.c*
)

add_executable(pgadmin ${PGADMIN_SUBSYSTEM}
    pgAdmin3.cpp
    ${PGADMIN_SOURCES}
)

if(WIN32)
    target_sources(pgadmin PRIVATE pgAdmin3.rc)
endif()

set(PGADMIN_PQ_INCLUDES ${PostgreSQL_INCLUDE_DIRS})
list(FILTER PGADMIN_PQ_INCLUDES EXCLUDE REGEX "[/\\\\]server$")

target_include_directories(pgadmin PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PGADMIN_PQ_INCLUDES}
    ${LIBXML2_INCLUDE_DIR}
    ${LIBXSLT_INCLUDE_DIR}
)

target_compile_definitions(pgadmin PRIVATE
    wxUSE_UNICODE
    PG_SSL
    ${wxWidgets_DEFINITIONS}
    $<$<CONFIG:Debug>:_DEBUG>
)

if(wxWidgets_DEFINITIONS_DEBUG)
    target_compile_definitions(pgadmin PRIVATE
        $<$<CONFIG:Debug>:${wxWidgets_DEFINITIONS_DEBUG}>
    )
endif()

if(WIN32)
    target_compile_definitions(pgadmin PRIVATE WIN32)
endif()

# A Windows find that never named a toolkit is an MSW DLL build.
# wx-config (GTK, Motif, X11, OS X, MSW) supplies its own defines.
if(WIN32 AND NOT wxWidgets_DEFINITIONS MATCHES "__WX")
    target_compile_definitions(pgadmin PRIVATE WXUSINGDLL __WXMSW__ STRICT)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(pgadmin PRIVATE
        -Wno-deprecated-declarations
        -Wno-deprecated
        -Wno-narrowing
        -Wno-unused-variable
        -Wno-unused-but-set-variable
        -Wno-unused-function
        -Wno-reorder
        -Wno-sign-compare
        -Wno-misleading-indentation
        -Wno-class-memaccess
        -Wno-catch-value
        -Wno-parentheses
        -Wno-unused-local-typedefs
    )
endif()

target_precompile_headers(pgadmin PRIVATE include/precomp.h)

target_link_libraries(pgadmin PRIVATE
    ${wxWidgets_LIBRARIES}
    ${PostgreSQL_LIBRARIES}
    ${LIBXML2_LIBRARIES}
    ${LIBXSLT_LIBRARIES}
)

if(WIN32)
    target_link_libraries(pgadmin PRIVATE ws2_32 shlwapi version oleacc comctl32 uuid oleaut32)
endif()

# Dialogs load ui/*.xrc from the source tree (../ui when the binary is in mingw64/).
# wxWidgets 3.2 is selected with wxWidgets_CONFIG_EXECUTABLE when several
# toolkits are installed. Do not add a PostgreSQL server-header include:
# catalogue SQL follows the connected server, not the libpq this binary linked.
