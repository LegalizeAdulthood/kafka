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
    install(TARGETS ${name} DESTINATION .)
endfunction()

foreach(grammar babble bill buttplug flame insult)
    kafka_target(${grammar})
endforeach()
