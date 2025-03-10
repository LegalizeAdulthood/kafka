cmake_minimum_required(VERSION 3.23)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(target_folder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set install folder
set(CMAKE_INSTALL_PREFIX install)

set(KAFKA_PROJECT_NAME "Kafka" CACHE "STRING" "Default project name for IDEs")
project("${KAFKA_PROJECT_NAME}" VERSION 1.1 LANGUAGES CXX)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT kafka)

add_subdirectory(config)
add_subdirectory(runtime)
add_subdirectory(kafka)
add_subdirectory(grammars)
add_subdirectory(packaging)

install(FILES LICENSE.txt DESTINATION .)
