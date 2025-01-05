cmake_minimum_required(VERSION 3.22)

add_library(imgui "")

target_sources(imgui
        PRIVATE
        "imconfig.h"
        "imgui.h"
        "imgui.cpp"
        "imgui_draw.cpp"
        "imgui_demo.cpp"
        "imgui_internal.h"
        "imgui_widgets.cpp"
        "imgui_tables.cpp"
        "imstb_rectpack.h"
        "imstb_textedit.h"
        "imstb_truetype.h"
)

target_link_libraries(imgui)