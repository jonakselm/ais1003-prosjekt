cmake_minimum_required(VERSION 3.15)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(tetris main.cpp source/Board.cpp source/GameBoard.cpp)
target_include_directories(tetris PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(tetris PRIVATE threepp::threepp imgui::imgui)
