#ifndef THREEPP_TETRIS_BOARD_HPP
#define THREEPP_TETRIS_BOARD_HPP

#include "Tetromino.hpp"
#include <array>
#include <vector>

class Board
{
public:
    enum class Direction { Down, Left, Right };
    static constexpr int BOARD_SIZE = 200;

public:
    Board();

    virtual void clearLine(int lineNumber) = 0;

protected:
    const virtual std::array<int, BOARD_SIZE> &getBoard() const;

    virtual void update(float dt) = 0;

    bool canMove(Direction dir, const Tetromino & t) const;

    void groundTetromino(const Tetromino &t);

protected:
    int m_width = 10, m_height = 20;
    std::array<int, BOARD_SIZE> m_board;
};

#endif//THREEPP_TETRIS_BOARD_HPP
