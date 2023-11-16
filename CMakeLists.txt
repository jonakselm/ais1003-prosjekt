cmake_minimum_required(VERSION 3.15)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(tetris main.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/source)

target_include_directories(tetris PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(tetris PRIVATE threepp::threepp imgui::imgui
                                PUBLIC libBoard)

# ============================
# Testing
# ============================

# Download Catch2 unit-test framework from GitHub
include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.3.2
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/tests)