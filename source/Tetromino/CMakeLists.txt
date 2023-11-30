add_library(libTetromino Tetromino.cpp)
target_include_directories(libTetromino PUBLIC ${CMAKE_SOURCE_DIR}/include
                                PUBLIC ${CMAKE_SOURCE_DIR}/include/Tetromino)