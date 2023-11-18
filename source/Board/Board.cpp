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

bool Board::canDo(Action action, const Tetromino & t) const
{
    const int width = t.getWidth();
    for (int y = 0; y < t.getHeight(); y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned int rotation = t.getRotation();
            switch (action)
            {
            case Action::RotateLeft:
                rotation -= 1;
                break;
            case Action::RotateRight:
                rotation += 1;
                break;
            }
            int nextX = x + t.posX;
            int nextY = y + t.posY;
            bool hasBrick = t.getElement(x, y, rotation);
            if (hasBrick)
            {
                // Constructs nextX and nextY
                switch (action)
                {
                case Action::MoveDown:
                {
                    nextY += 1;
                }
                break;
                case Action::MoveLeft:
                {
                    nextX -= 1;
                    break;
                }
                case Action::MoveRight:
                {
                    nextX += 1;
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
                if (boardHasBrick)
                {
                    return false;
                }
                switch (action)
                {
                case Action::MoveDown:
                    if ((nextY > m_height))
                    {
                        return false;
                    }
                    break;
                case Action::MoveLeft:
                    if (nextX < 0)
                    {
                        return false;
                    }
                    break;
                case Action::MoveRight:
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
