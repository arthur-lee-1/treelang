add_library(treelang_core
    nothing.cpp
    core/matrix.hpp
)

target_link_libraries(treelang_core PUBLIC pjh_result pjh_json pjh_cli pjh_platform)

target_include_directories(treelang_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(treelang
    main.cpp
)

target_link_libraries(treelang PRIVATE treelang_core)
