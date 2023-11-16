#include "Board/Board.hpp"
#include <algorithm>

Board::Board()
    :
    m_board({ 0 })
{
    /*for (auto &cell : m_board)
    {
        cell = 1;
    }*/
    /*for (int y = 0; y < m_tetromino.getHeight(); y++)
    {
        for (int x = 0; x < m_tetromino.getWidth(); x++)
        {
            if (m_tetromino.getElement(x, y))
            {
                m_board[x + y * m_width] = 1;
            }
        }
    }*/
}

void Board::clearLine(int lineNumber)
{
    auto start = m_board.begin() + lineNumber * m_width;
    auto end = start + m_width;
    std::fill(start, end, 0);
    std::rotate(m_board.begin(), start, end);
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
    for (int i = 0; i < m_height; i++)
    {
        int rowStartIndex = i * m_width;
        const auto rowBegin = m_board.begin() + rowStartIndex;
        int amountFilled = std::count(rowBegin, rowBegin + m_width, 1);
        if (amountFilled >= 10)
        {
            clearLine(i);
            Board::clearLine(i);
        }
    }
}

bool Board::canMove(Board::Direction dir, const Tetromino & t) const
{
    std::vector<bool> v;
    const int width = t.getWidth();
    for (int y = 0; y < t.getHeight(); y++)
    {
        for (int x = 0; x < width; x++)
        {
            int nextX = 0;
            int nextY = 0;
            v.push_back(t.getElement(x, y));
            bool hasBrick = t.getElement(x, y);
            if (hasBrick)
            {
                // Constructs nextX and nextY
                switch (dir)
                {
                case Direction::Down:
                {
                    nextX = x + t.posX;
                    nextY = y + t.posY + 1;
                }
                break;
                case Direction::Left:
                {
                    nextX = x + t.posX - 1;
                    nextY = y + t.posY;
                    break;
                }
                case Direction::Right:
                {
                    nextX = x + t.posX + 1;
                    nextY = y + t.posY;
                    break;
                }
                }

                // Conditionals
                unsigned int index = nextX + nextY * m_width;
                if (index > m_board.size())
                {
                    return false;
                }
                bool boardHasBrick = m_board[index];
                switch (dir)
                {
                case Direction::Down:
                    if ((boardHasBrick) ||
                        (nextY > m_height))
                    {
                        return false;
                    }
                    break;
                case Direction::Left:
                    if (nextX < 0)
                    {
                        return false;
                    }
                    break;
                case Direction::Right:
                    if (nextX >= m_width)
                    {
                        return false;
                    }
                    break;
                }
            }
        }
    }
    return true;
}
