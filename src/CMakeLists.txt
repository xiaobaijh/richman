set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES place player gutil gsystem common display tips)

add_library(src ${SOURCES})

find_package(Curses REQUIRED)
target_link_libraries(src ${CURSES_LIBRARIES})
set_target_properties(src PROPERTIES OUTPUT_NAME "richman_src")
