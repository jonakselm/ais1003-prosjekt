add_library(libBoard Board.cpp GameBoard.cpp BoardController.cpp
                BoardView.cpp)
target_include_directories(libBoard PUBLIC ${CMAKE_SOURCE_DIR}/include
                                   PUBLIC ${CMAKE_SOURCE_DIR}/include/Board)

find_package(threepp CONFIG REQUIRED)
target_link_libraries(libBoard PRIVATE threepp::threepp
                                PUBLIC libTetromino)