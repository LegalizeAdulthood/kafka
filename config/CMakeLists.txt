set(HAS_GETPID OFF)
check_include_file(process.h HAS_PROCESS_H)
check_include_file(unistd.h HAS_UNISTD_H)
if(HAS_PROCESS_H AND NOT HAS_GETPID)
    check_symbol_exists(getpid "process.h" HAS_GETPID)
    set(GETPID_HEADER "process")
endif()
if(HAS_UNISTD_H AND NOT HAS_GETPID)
    check_symbol_exists(getpid "unistd.h" HAS_GETPID)
    set(GETPID_HEADER "unistd")
endif()
if(NOT HAS_GETPID)
    message(FATAL_ERROR "Couldn't find getpid() in unistd.h or process.h")
endif()

configure_file(getpid.${GETPID_HEADER}.h.in         include/config/getpid.h @ONLY)

add_library(config INTERFACE
    getpid.unistd.h.in getpid.process.h.in
    "${CMAKE_CURRENT_BINARY_DIR}/include/config/getpid.h"
)
target_include_directories(config INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/include" .)
set_target_properties(config PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER "Libraries")
source_group("CMake Templates" REGULAR_EXPRESSION "^.*\\.in$")
