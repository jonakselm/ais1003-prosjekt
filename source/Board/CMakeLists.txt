add_library(libBoard Board.cpp BoardController.cpp
                BoardView.cpp)
target_include_directories(libBoard PUBLIC ${CMAKE_SOURCE_DIR}/include
                                   PUBLIC ${CMAKE_SOURCE_DIR}/include/Board)

target_link_libraries(libBoard PRIVATE sfml-window
							   		   sfml-system
									   sfml-graphics
                                	   libTetromino)
