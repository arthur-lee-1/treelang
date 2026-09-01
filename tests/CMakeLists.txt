add_executable(treelang_tests test_smoke.cpp)

target_link_libraries(treelang_tests PRIVATE treelang_core)

target_compile_definitions(treelang_tests PRIVATE TREELANG_BUILD_TESTS)

add_test(NAME treelang_tests COMMAND treelang_tests)

add_executable(core_matrix_tests core/matrix_test.cpp)

target_link_libraries(core_matrix_tests PRIVATE treelang_core)

add_test(NAME core_matrix_tests COMMAND core_matrix_tests)
