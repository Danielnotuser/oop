cmake_minimum_required(VERSION 3.16)
project(oopsemcon)

add_compile_options(--coverage)
add_link_options(--coverage)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

add_library(stud lib/stud.h src/stud.cpp src/senior.cpp)
add_library(group lib/group.h src/group.cpp)
add_library(app lib/app.h src/app.cpp)
add_library(menu lib/menu.h src/menu.cpp)
add_library(table INTERFACE lib/table.h lib/table.tcc)
link_libraries(stud group app table menu)

add_executable(main src/main.cpp)
add_executable(test tests/tests.cpp)

target_link_libraries(main stud group app table menu)
