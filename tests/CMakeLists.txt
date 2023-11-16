add_executable(Tests tests.cpp)
add_test(NAME Tests COMMAND Tests)

target_link_libraries(Tests PRIVATE Catch2::Catch2WithMain
                            PUBLIC libBoard)