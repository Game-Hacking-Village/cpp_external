cmake_minimum_required(VERSION 3.31)
project(gh_external)

set(CMAKE_CXX_STANDARD 26)

# simple game
add_executable(game simple_game/simple_game.cpp)

# external lib dependencies
set(external_lib external/process.cpp external/memory.cpp)
# simple external (read and write memory)
add_executable(external_simple external/external_simple.cpp ${external_lib})

# doom external gui (specifics to doom)
set(imgui_dir external/imgui)
include_directories(${imgui_dir} ${imgui_dir}/backends ${imgui_dir}/misc/cpp)
set(IMGUI_SOURCE
        ${imgui_dir}/imgui.cpp
        ${imgui_dir}/imgui_draw.cpp
        ${imgui_dir}/imgui_widgets.cpp
        ${imgui_dir}/imgui_tables.cpp
        ${imgui_dir}/misc/cpp/imgui_stdlib.cpp
        ${imgui_dir}/backends/imgui_impl_dx11.cpp
        ${imgui_dir}/backends/imgui_impl_win32.cpp
)
add_executable(external_doom_gui
        external/external_doom_gui.cpp
        external/doom/doom.cpp
        ${external_lib}
        ${IMGUI_SOURCE}
)
target_link_libraries(external_doom_gui d3d11 d3dcompiler dwmapi)