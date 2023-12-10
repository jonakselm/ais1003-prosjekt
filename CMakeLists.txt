cmake_minimum_required(VERSION 3.15)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(tetris main.cpp)

add_subdirectory(${CMAKE_SOURCE_DIR}/source)

target_include_directories(tetris PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(tetris PRIVATE sfml-window
							 		 sfml-system
									 sfml-graphics
							 		 libBoard)
