#ifndef THREEPP_TETRIS_BOARD_HPP
#define THREEPP_TETRIS_BOARD_HPP

#include "../Tetromino/Tetromino.hpp"
#include <array>
#include <vector>

class Board
{
public:
    enum class Action { MoveDown, MoveLeft, MoveRight,
                        RotateLeft, RotateRight };
    static constexpr int BOARD_SIZE = 200;
    static constexpr int WIDTH = 10;
    static constexpr int HEIGHT = 20;

    Board();

    void clearLine(int lineNumber);

    const std::array<int, BOARD_SIZE> &getBoard() const;

    void resetBoard();

    bool canDo(Action action, const Tetromino &t) const;

    // Returns bit flags of lines that are cleared
    int groundTetromino(const Tetromino &t);

private:
    std::array<int, BOARD_SIZE> m_board;
};

#endif//THREEPP_TETRIS_BOARD_HPP
