#include "Board/Board.hpp"
#include <algorithm>

Board::Board()
    :
    m_board({ 0 })
{
}

void Board::clearLine(int lineNumber)
{
    auto start = m_board.begin() + lineNumber * WIDTH;
    auto end = start + WIDTH;
    std::fill(start, end, 0);
    std::rotate(m_board.begin(), start, end);
}

const std::array<int, 200>& Board::getBoard() const
{
    return m_board;
}

void Board::resetBoard()
{
    std::fill(m_board.begin(), m_board.end(), 0);
}

int Board::groundTetromino(const Tetromino &t)
{
    for (int y = 0; y < t.getHeight(); y++)
    {
        for (int x = 0; x < t.getWidth(); x++)
        {
            if (int color = t.getElement(x, y))
            {
                int i = x + t.posX + (y + t.posY) * WIDTH;
                if (i > 0)
                {
                    m_board[i] = color;
                }
            }
        }
    }
    int flags = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        int rowStartIndex = i * WIDTH;
        const auto rowBegin = m_board.begin() + rowStartIndex;
        if (std::all_of(rowBegin, rowBegin + WIDTH, [](bool b){ return b == 1; }))
        {
            flags += 1 << i;
        }
    }
    return flags;
}

bool Board::canDo(Action action, const Tetromino &t) const
{
    const int width = t.getWidth();
    // Set up for checking a rotated tetro
    unsigned int rotation = t.rotation;
    switch (action)
    {
    case Action::RotateLeft:
        rotation -= 1;
        break;
    case Action::RotateRight:
        rotation += 1;
        break;
    }
    for (int y = 0; y < t.getHeight(); y++)
    {
        for (int x = 0; x < width; x++)
        {
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
                unsigned int index = nextX + nextY * WIDTH;
                if (index >= m_board.size())
                {
                    return false;
                }
                bool boardHasBrick = m_board[index];
                if (boardHasBrick)
                {
                    return false;
                }
                // Action specific conditionals
                switch (action)
                {
                case Action::MoveDown:
                    if ((nextY > HEIGHT))
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
                    if (nextX >= WIDTH)
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
