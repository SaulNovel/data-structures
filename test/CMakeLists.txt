set(BINARY data-structures_test)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true *.h *.cpp)

add_executable(
    ${BINARY} 
    ${TEST_SOURCES}
)

target_link_libraries(
    ${BINARY} 
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${BINARY})