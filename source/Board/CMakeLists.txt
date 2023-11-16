add_library(libBoard Board.cpp GameBoard.cpp)
target_include_directories(libBoard PUBLIC ${CMAKE_SOURCE_DIR}/include)

find_package(threepp CONFIG REQUIRED)
target_link_libraries(libBoard PRIVATE threepp::threepp)