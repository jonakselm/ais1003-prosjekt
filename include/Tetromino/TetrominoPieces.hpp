

#ifndef TETRIS_TETROMINOPIECES_HPP
#define TETRIS_TETROMINOPIECES_HPP

#include "Tetromino.hpp"

class TetroI : public Tetromino
{
public:
    TetroI() : Tetromino::Tetromino(4, 4)
    {
        m_cells[4] = Color::Cyan;
        m_cells[5] = Color::Cyan;
        m_cells[6] = Color::Cyan;
        m_cells[7] = Color::Cyan;
    }
};

class TetroO : public Tetromino
{
public:
    TetroO() : Tetromino::Tetromino(2, 2)
    {
        m_cells[0] = Color::Yellow;
        m_cells[1] = Color::Yellow;
        m_cells[2] = Color::Yellow;
        m_cells[3] = Color::Yellow;
    }
};

class TetroT : public Tetromino
{
public:
    TetroT() : Tetromino::Tetromino(3, 3)
    {
        m_cells[1] = Color::Purple;
        m_cells[3] = Color::Purple;
        m_cells[4] = Color::Purple;
        m_cells[5] = Color::Purple;
    }
};

class TetroJ : public Tetromino
{
public:
    TetroJ() : Tetromino::Tetromino(3, 3)
    {
        m_cells[1] = Color::Blue;
        m_cells[4] = Color::Blue;
        m_cells[6] = Color::Blue;
        m_cells[7] = Color::Blue;
    }
};

class TetroL : public Tetromino
{
public:
    TetroL() : Tetromino::Tetromino(3, 3)
    {
        m_cells[1] = Color::Orange;
        m_cells[4] = Color::Orange;
        m_cells[7] = Color::Orange;
        m_cells[8] = Color::Orange;
    }
};

class TetroS : public Tetromino
{
public:
    TetroS() : Tetromino::Tetromino(3, 3)
    {
        m_cells[1] = Color::Green;
        m_cells[2] = Color::Green;
        m_cells[3] = Color::Green;
        m_cells[4] = Color::Green;
    }
};

class TetroZ : public Tetromino
{
public:
    TetroZ() : Tetromino::Tetromino(3, 3)
    {
        m_cells[0] = Color::Red;
        m_cells[1] = Color::Red;
        m_cells[4] = Color::Red;
        m_cells[5] = Color::Red;
    }
};

#endif//TETRIS_TETROMINOPIECES_HPP
