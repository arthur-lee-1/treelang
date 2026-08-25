add_library(treelang_core
    nothing.cpp
)

target_link_libraries(treelang_core PUBLIC pjh_result pjh_json pjh_cli pjh_platform)

add_executable(treelang
    main.cpp
)

target_link_libraries(treelang PRIVATE treelang_core)
