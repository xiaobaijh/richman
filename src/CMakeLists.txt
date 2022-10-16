set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

set(SOURCES player.cpp place.cpp)

add_library(src ${SOURCES})

target_link_libraries(src)

set_target_properties(src PROPERTIES OUTPUT_NAME "richman_src")

