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

# Embed ui/*.xrc as C++ on every platform. wxrc writes InitXmlResource(),
# which pgAdmin3.cpp calls when EMBED_XRC is set. Windows RCDATA in the
# .rc file cannot carry these dialogs on GTK, Motif, X11 or macOS, and a
# runtime load of ui/*.xrc becomes "/*.xrc" when the binary is not next to
# the source tree.
file(GLOB PGADMIN_XRC_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.xrc")
if(NOT PGADMIN_XRC_FILES)
    message(FATAL_ERROR "pgadmin: no ui/*.xrc files to embed")
endif()

if(NOT wxWidgets_wxrc_EXECUTABLE)
    find_program(wxWidgets_wxrc_EXECUTABLE NAMES wxrc wxrc-3.2 wxrc-3.1)
endif()
if(NOT wxWidgets_wxrc_EXECUTABLE)
    message(FATAL_ERROR "pgadmin: wxrc is required to embed ui/*.xrc")
endif()

set(PGADMIN_XRC_NAMES)
foreach(xrc_path ${PGADMIN_XRC_FILES})
    get_filename_component(xrc_name "${xrc_path}" NAME)
    list(APPEND PGADMIN_XRC_NAMES "${xrc_name}")
endforeach()
list(SORT PGADMIN_XRC_NAMES)

set(PGADMIN_XRC_CPP "${CMAKE_CURRENT_BINARY_DIR}/xrcDialogs.cpp")
add_custom_command(
    OUTPUT "${PGADMIN_XRC_CPP}"
    COMMAND "${wxWidgets_wxrc_EXECUTABLE}" -c -o "${PGADMIN_XRC_CPP}" ${PGADMIN_XRC_NAMES}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/ui"
    DEPENDS ${PGADMIN_XRC_FILES}
    COMMENT "Embedding ui/*.xrc"
    VERBATIM
)
target_sources(pgadmin PRIVATE "${PGADMIN_XRC_CPP}")
# Only pgAdmin3.cpp branches on EMBED_XRC. Keep the define off the other
# translation units so a resource rebuild does not recompile the tree.
set_source_files_properties(pgAdmin3.cpp PROPERTIES
    COMPILE_DEFINITIONS EMBED_XRC
)
set_source_files_properties("${PGADMIN_XRC_CPP}" PROPERTIES
    SKIP_PRECOMPILE_HEADERS ON
    COMPILE_OPTIONS "$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-O0>;$<$<CXX_COMPILER_ID:MSVC>:/Od>"
)

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

# Dialog resources are compiled into the binary (see the wxrc step above).
# wxWidgets 3.2 is selected with wxWidgets_CONFIG_EXECUTABLE when several
# toolkits are installed. Do not add a PostgreSQL server-header include:
# catalogue SQL follows the connected server, not the libpq this binary linked.
