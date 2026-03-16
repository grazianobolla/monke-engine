cmake_minimum_required(VERSION 3.25.0)
project(monke-project)

# compile engine & playground
set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SOURCES "src/*.cpp" "demo/*.cpp")

# glm
add_subdirectory(external/glm)

# glad
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include )

# glfw
add_subdirectory(external/glfw)

# stb
add_library(stb external/stb/stb_image.cpp)

# imgui
set(IMGUI_DIR external/imgui)

add_library(imgui
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

target_link_libraries(imgui PUBLIC glfw)

add_executable(monke ${SOURCES})
target_include_directories(monke PUBLIC include)
target_link_libraries(monke PRIVATE glm glad glfw imgui stb)

# copy resource folder
file(COPY ./demo/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})