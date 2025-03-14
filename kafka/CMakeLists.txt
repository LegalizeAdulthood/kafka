set(LEXER_FLAGS "")
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    include(FetchContent)
    FetchContent_Declare(download_bison
        URL "https://github.com/lexxmark/winflexbison/releases/download/v2.5.25/win_flex_bison-2.5.25.zip"
        URL_MD5 "720226b1befe7033fb3ecc98f5ffd425"
        DOWNLOAD_EXTRACT_TIMESTAMP FALSE)
    FetchContent_MakeAvailable(download_bison)
    set(BISON_ROOT "${download_bison_SOURCE_DIR}")
    set(FLEX_ROOT "${download_bison_SOURCE_DIR}")
    message(STATUS "BISON_ROOT=${BISON_ROOT}")
    set(LEXER_FLAGS "-DYY_NO_UNISTD_H")
endif()
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

bison_target(parser parse.y "${CMAKE_CURRENT_BINARY_DIR}/kafka_parser.cpp"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/kafka_parser.h")
flex_target(lexer lexical.l "${CMAKE_CURRENT_BINARY_DIR}/kafka_lexer.cpp"
    COMPILE_FLAGS "${LEXER_FLAGS}"
    DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/kafka_lexer.h")
add_flex_bison_dependency(lexer parser)

add_executable(kafka
    ast.h
    dstrans.h dstrans.cpp
    init.h init.cpp
    main.cpp
    psubr.h psubr.cpp
    stuff.h stuff.cpp
    parse.y
    lexical.l
    ${FLEX_lexer_OUTPUTS}
    ${BISON_parser_OUTPUTS}
)
source_group("Parser Files" REGULAR_EXPRESSION "^.*\\.[ly]$")
target_include_directories(kafka PUBLIC . "${CMAKE_CURRENT_BINARY_DIR}")
target_link_libraries(kafka PUBLIC runtime)
target_folder(kafka "Tools")

install(TARGETS kafka DESTINATION .)
