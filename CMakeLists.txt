cmake_minimum_required(VERSION 3.26.1)
project(monke-project)

# compile engine & playground
add_compile_options(-std=c++17)
file(GLOB_RECURSE SOURCES "src/*.cpp" "demo/*.cpp")
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(monkexe ${SOURCES})
target_include_directories(monkexe PUBLIC include)
target_link_libraries(monkexe -limgui -lglfw)
