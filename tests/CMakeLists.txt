set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

set(SOURCES test.cpp )

add_library(tests ${SOURCES})

target_link_libraries(tests)

set_target_properties(tests PROPERTIES OUTPUT_NAME "richman_test")

