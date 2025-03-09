cmake_minimum_required(VERSION 3.23)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(target_folder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(KAFKA_PROJECT_NAME "Kafka" CACHE "STRING" "Default project name for IDEs")
project("${KAFKA_PROJECT_NAME}" CXX)

include(CTest)

set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT kafka)

function(kafka_target name)
    add_executable(${name}
        ${name}.k
        "${CMAKE_CURRENT_BINARY_DIR}/${name}.spec.cpp"
        "${CMAKE_CURRENT_BINARY_DIR}/${name}.text.cpp"
    )
    source_group("Kafka Files" REGULAR_EXPRESSION ".*\\.k$")
    target_link_libraries(${name} PUBLIC runtime)
    set_target_properties(${name} PROPERTIES
        LINKER_LANGUAGE CXX
        FOLDER "Kafka Generators")
    add_custom_command(OUTPUT
            "${CMAKE_CURRENT_BINARY_DIR}/${name}.spec.cpp"
            "${CMAKE_CURRENT_BINARY_DIR}/${name}.text.cpp"
        COMMAND kafka -t "${name}.text.cpp" -s "${name}.spec.cpp" "${CMAKE_CURRENT_LIST_DIR}/${name}.k"
        MAIN_DEPENDENCY ${name}.k
        DEPENDS kafka
        COMMENT "Kafka ${name}"
    )
endfunction()

foreach(grammar babble bill buttplug flame insult)
    kafka_target(${grammar})
endforeach()

add_subdirectory(config)
add_subdirectory(runtime)
add_subdirectory(kafka)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
