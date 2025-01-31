configure_file(getpid.${CMAKE_SYSTEM_NAME}.h.in         include/config/getpid.h @ONLY)

add_library(config INTERFACE
    getpid.Linux.h.in getpid.Windows.h.in
    "${CMAKE_CURRENT_BINARY_DIR}/include/config/getpid.h"
)
target_include_directories(config INTERFACE "${CMAKE_CURRENT_BINARY_DIR}/include" .)
set_target_properties(config PROPERTIES
    LINKER_LANGUAGE CXX
    FOLDER "Libraries")
source_group("CMake Templates" REGULAR_EXPRESSION "^.*\\.in$")
