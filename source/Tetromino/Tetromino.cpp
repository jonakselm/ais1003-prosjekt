#include "Tetromino.hpp"

void Tetromino::incrementRotation()
{
    m_rotation++;
}

void Tetromino::decrementRotation()
{
    m_rotation--;
}

int Tetromino::getWidth() const
{
    return m_width;
}

int Tetromino::getHeight() const
{
    return m_height;
}

unsigned int Tetromino::getRotation() const
{
    return m_rotation;
}

int Tetromino::getElement(int x, int y, unsigned int rotation) const
{
    switch (rotation % 4)
    {
    case 0:
        return m_cells[x + m_width * y];
        break;
    case 1:
        return m_cells[(m_height - 1 - x) * m_width + y];
        break;
    case 2:
        return m_cells[(m_height - y) * m_width - 1 - x];
        break;
    case 3:
        return m_cells[m_width - 1 + x * m_width - y];
        break;
    }
    return false;
}

int Tetromino::getElement(int x, int y) const
{
    return getElement(x, y, m_rotation);
}

Tetromino::Tetromino(int width, int height)
    : m_width(width),
      m_height(height)
{
    int size = width * height;
    m_cells.reserve(size);
    for (int i = 0; i < size; i++)
    {
        m_cells.push_back(false);
    }
}
