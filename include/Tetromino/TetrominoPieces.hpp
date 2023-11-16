

#ifndef TETRIS_TETROMINOPIECES_HPP
#define TETRIS_TETROMINOPIECES_HPP

#include "Tetromino.hpp"

class TetroI : public Tetromino
{
public:
    TetroI() : Tetromino::Tetromino(4, 4, Color::Cyan)
    {
        m_cells[8] = true;
        m_cells[9] = true;
        m_cells[10] = true;
        m_cells[11] = true;
    }
};

class TetroO : public Tetromino
{
public:
    TetroO() : Tetromino::Tetromino(2, 2, Color::Yellow)
    {
        m_cells[0] = true;
        m_cells[1] = true;
        m_cells[2] = true;
        m_cells[3] = true;
    }
};

class TetroT : public Tetromino
{
public:
    TetroT() : Tetromino::Tetromino(3, 3, Color::Purple)
    {
        m_cells[1] = true;
        m_cells[3] = true;
        m_cells[4] = true;
        m_cells[5] = true;
    }
};

class TetroJ : public Tetromino
{
public:
    TetroJ() : Tetromino::Tetromino(3, 3, Color::Blue)
    {
        m_cells[1] = true;
        m_cells[4] = true;
        m_cells[6] = true;
        m_cells[7] = true;
    }
};

class TetroL : public Tetromino
{
public:
    TetroL() : Tetromino::Tetromino(3, 3, Color::Orange)
    {
        m_cells[1] = true;
        m_cells[4] = true;
        m_cells[7] = true;
        m_cells[8] = true;
    }
};

class TetroS : public Tetromino
{
public:
    TetroS() : Tetromino::Tetromino(3, 3, Color::Green)
    {
        m_cells[1] = true;
        m_cells[2] = true;
        m_cells[3] = true;
        m_cells[4] = true;
    }
};

class TetroZ : public Tetromino
{
public:
    TetroZ() : Tetromino::Tetromino(3, 3, Color::Red)
    {
        m_cells[0] = true;
        m_cells[1] = true;
        m_cells[4] = true;
        m_cells[5] = true;
    }
};

#endif//TETRIS_TETROMINOPIECES_HPP
