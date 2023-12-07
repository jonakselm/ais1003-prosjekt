#include <catch2/catch_test_macros.hpp>
#include "Board/Board.hpp"
#include "Tetromino/TetrominoPieces.hpp"
#include <memory>

TEST_CASE("Clear Lines")
{
    Board board;
    std::vector<std::unique_ptr<Tetromino>> v;
    v.emplace_back(std::make_unique<TetroI>());
    v.emplace_back(std::make_unique<TetroI>());
    v.back()->posX = 4;
    v.emplace_back(std::make_unique<TetroO>());
    v.back()->posX = 8;
    int toClear = 0;
    for (auto &t : v)
    {
        while (board.canDo(Board::Action::MoveDown, *t))
        {
            t->posY += 1;
        }
        toClear = board.groundTetromino(*t);
    }
    auto prevBoard = board.getBoard();
    for (int i = 0; i < Board::HEIGHT; i++)
    {
        if (toClear & 1 << i)
        {
            board.clearLine(i);
        }
    }
    auto currBoard = board.getBoard();

    for (int i = 0; i < Board::WIDTH; i++)
    {
        CHECK(prevBoard[180 + i] == currBoard[190 + i]);
    }
}