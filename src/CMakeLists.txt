set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-lncursesw)
set(SOURCES place player gutil gsystem common display tips)

add_library(src ${SOURCES})

set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)
find_package(Curses REQUIRED)
target_link_libraries(src ${NCURSES_LIBRARIES})
set_target_properties(src PROPERTIES OUTPUT_NAME "richman_src")
