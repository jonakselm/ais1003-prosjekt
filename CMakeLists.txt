cmake_minimum_required(VERSION 3.15)
project(threepp_vcpkg_demo)

set(CMAKE_CXX_STANDARD 20)

find_package(threepp CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

add_executable(demo main.cpp source/Board.cpp source/GameBoard.cpp)
target_include_directories(demo PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(demo PRIVATE threepp::threepp imgui::imgui)
