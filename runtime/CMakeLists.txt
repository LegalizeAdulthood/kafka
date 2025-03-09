add_library(runtime
    defs.h
    kafgraf.h
    etc.cpp
    maketext.h maketext.cpp
    node_type.h
    output.h output.cpp
    runtime.h
)
target_include_directories(runtime PUBLIC .)
target_link_libraries(runtime PUBLIC config)
target_folder(runtime "Libraries")
