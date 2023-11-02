#include "Board.hpp"
#include <algorithm>

Board::Board()
    :
    m_board({ 0 })
{
    /*for (auto &cell : m_board)
    {
        cell = 1;
    }*/
    /*for (int y = 0; y < tetromino.getHeight(); y++)
    {
        for (int x = 0; x < tetromino.getWidth(); x++)
        {
            if (tetromino.getElement(x, y))
            {
                m_board[x + y * m_width] = 1;
            }
        }
    }*/
}

void Board::clearLine(int lineNumber)
{
    auto start = m_board.begin() + lineNumber * m_width;
    auto end = m_board.begin() + (lineNumber + 1) * m_width;
    std::fill(start, end, 0);
    long zeros = std::count(m_board.begin(), start, 0);
    std::rotate(m_board.begin() + zeros, start, m_board.end());
}

const std::array<int, 200>& Board::getBoard() const
{
    return m_board;
}

void Board::update(float dt)
{
}

void Board::groundTetromino(const Tetromino & t)
{
    for (int y = 0; y < t.getHeight(); y++)
    {
        for (int x = 0; x < t.getWidth(); x++)
        {
            if (t.getElement(x, y))
            {
                m_board[x + t.posX + (y + t.posY) * m_width] = 1;
            }
        }
    }
}
bool Board::canMove(Board::Direction dir, const Tetromino &tetromino) const
{
    switch (dir)
    {
    case Direction::Down:
    {
        const int width = tetromino.getWidth();
        for (int y = 0; y < tetromino.getHeight(); y++)
        {
            for (int x = 0; x < width; x++)
            {
                int totalX = x + tetromino.posX;
                int noge = tetromino.posY;
                int nextY = y + tetromino.posY + 1;
                bool hasBrick = tetromino.getElement(x, y);
                bool boardHasBrick = m_board[totalX + nextY * m_width];
                if ((hasBrick && boardHasBrick) ||
                    (nextY > m_height))
                {
                    return false;
                }
            }
        }
    }
    case Direction::Left:
    {

    }
    case Direction::Right:
    {

    }
    }
    return true;
}
