#ifndef THREEPP_TETRIS_BOARD_HPP
#define THREEPP_TETRIS_BOARD_HPP

#include "Tetromino/Tetromino.hpp"
#include <array>
#include <vector>

class Board
{
public:
    enum class Action { MoveDown, MoveLeft, MoveRight,
                        RotateLeft, RotateRight };
    static constexpr int BOARD_SIZE = 200;

protected:
    Board();

    virtual void clearLine(int lineNumber) = 0;

    const virtual std::array<int, BOARD_SIZE> &getBoard() const;

    virtual void update(float dt) = 0;

    bool canDo(Action action, const Tetromino &t) const;

    void groundTetromino(const Tetromino &t);


    int m_width = 10, m_height = 20;
    std::array<int, BOARD_SIZE> m_board;
};

#endif//THREEPP_TETRIS_BOARD_HPP