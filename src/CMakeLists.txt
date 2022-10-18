set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)


set(CMAKE_CXX_STANDARD 11)


set(SOURCES place player util gsystem common)

include_directories(${PROJECT_SOURCE_DIR}/csrc)

add_library(src ${SOURCES})

target_link_libraries(src)

set_target_properties(src PROPERTIES OUTPUT_NAME "richman_src")

