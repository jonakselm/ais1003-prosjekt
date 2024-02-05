add_library(libBoard Board.cpp BoardController.cpp
                BoardView.cpp)
target_include_directories(libBoard PUBLIC ${CMAKE_SOURCE_DIR}/include
                                   PUBLIC ${CMAKE_SOURCE_DIR}/include/Board)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)
target_link_libraries(libBoard PRIVATE SFML::Graphics
                                	   libTetromino)
