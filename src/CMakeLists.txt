add_library(treelang_core
    nothing.cpp
)

add_executable(treelang
    main.cpp
)

target_link_libraries(treelang PRIVATE treelang_core)
