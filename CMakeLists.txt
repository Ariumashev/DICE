cmake_minimum_required(VERSION 3.16)
project(DICE VERSION 1.0.0 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Options
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EDITOR "Build editor" ON)
option(ENABLE_NETWORK "Enable networking features" ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/external)

# Find packages
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(Lua REQUIRED)

# External libraries paths
set(IMGUI_DIR ${PROJECT_SOURCE_DIR}/external/imgui)
set(JSON_DIR ${PROJECT_SOURCE_DIR}/external/json)
set(SOL2_DIR ${PROJECT_SOURCE_DIR}/external/sol2)
set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/external/spdlog)

# ImGui sources
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Include ImGui headers
include_directories(${IMGUI_DIR})
include_directories(${IMGUI_DIR}/backends)
include_directories(${JSON_DIR}/include)
include_directories(${SOL2_DIR}/include)
include_directories(${SPDLOG_DIR}/include)
include_directories(${LUA_INCLUDE_DIR})

# Core library sources
file(GLOB_RECURSE CORE_SOURCES 
    "${PROJECT_SOURCE_DIR}/scr/core/*.cpp"
)

file(GLOB_RECURSE CORE_HEADERS
    "${PROJECT_SOURCE_DIR}/include/core/*.hpp"
)

# Create core library
add_library(dice_core STATIC
    ${CORE_SOURCES}
    ${CORE_HEADERS}
    ${IMGUI_SOURCES}
)

target_link_libraries(dice_core
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio
    ${LUA_LIBRARIES}
    GL
    dl
    pthread
)

# Main executable
add_executable(dice
    ${PROJECT_SOURCE_DIR}/scr/main.cpp
)

target_link_libraries(dice
    dice_core
)

# Editor executable (if enabled)
if(BUILD_EDITOR)
    file(GLOB_RECURSE EDITOR_SOURCES
        "${PROJECT_SOURCE_DIR}/scr/editor/*.cpp"
    )

    if(EDITOR_SOURCES)
        add_executable(dice_editor ${EDITOR_SOURCES})
        target_link_libraries(dice_editor dice_core)
    else()
        message(WARNING "BUILD_EDITOR=ON, but no editor sources found in scr/editor. Skipping dice_editor.")
    endif()
endif()


# Tests (if enabled)
if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    file(GLOB_RECURSE TEST_SOURCES
        "${PROJECT_SOURCE_DIR}/tests/*.cpp"
    )

    if(TEST_SOURCES)
        add_executable(dice_tests ${TEST_SOURCES})
        target_link_libraries(dice_tests
            dice_core
            GTest::GTest
            GTest::Main
            pthread
        )
        add_test(NAME dice_tests COMMAND dice_tests)
    else()
        message(WARNING "BUILD_TESTS=ON, but no test sources found in tests/. Skipping dice_tests.")
    endif()
endif()


# Installation
install(TARGETS dice DESTINATION bin)

# Устанавливаем редактор только если цель реально существует
if(TARGET dice_editor)
    install(TARGETS dice_editor DESTINATION bin)
endif()

# Аналогично для тестов (обычно тесты вообще не ставят, но пусть будет безопасно)
if(TARGET dice_tests)
    install(TARGETS dice_tests DESTINATION bin)
endif()


# Copy assets to build directory
file(COPY ${PROJECT_SOURCE_DIR}/asset DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/scripts DESTINATION ${CMAKE_BINARY_DIR})

# Print configuration
message(STATUS "DICE Configuration:")
message(STATUS "  Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Build tests: ${BUILD_TESTS}")
message(STATUS "  Build editor: ${BUILD_EDITOR}")
message(STATUS "  Enable network: ${ENABLE_NETWORK}")
message(STATUS "  C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "  SFML found: ${SFML_FOUND}")
message(STATUS "  Lua found: ${LUA_FOUND}")
