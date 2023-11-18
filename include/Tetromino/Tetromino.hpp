

#ifndef THREEPP_TETRIS_TETROMINO_HPP
#define THREEPP_TETRIS_TETROMINO_HPP

#include <vector>
#include <algorithm>

/* Took inspiration for the brick indexing from
 * Javidx9 on youtube
 * 4x4
 * Rotation 0: m_cells[x + m_width * y]
 * Rotation 1: m_cells[12 - x * m_width + y]
 * Rotation 2: m_cells[15 - x - y * m_width]
 * Rotation 3: m_cells[3 + m_width * x - y]
 *
 * General
 * Rotation 0: m_cells[x + m_width * y]
 * Rotation 1: m_cells[(m_height- 1 - x) * m_width + y]
 * Rotation 2: m_cells[(m_height - 1 - x - y) * m_width]
 * Rotation 3: m_cells[m_width - 1 + x * m_width - y]
 *
 * 3x3
 * Rotation 0: m_cells[x+m_width*y]
 * Rotation 1: m_cells[6 - x * m_width + y]
 * Rotation 2: m_cells[8 - x - y * m_width]
 * Rotation 3: m_cells[2 + x * m_width - y]
 */

class Tetromino
{
public:
    enum class Color { None, Cyan, Yellow, Purple, Blue, Orange, Green, Red };

    // Takes a number from 0-3
    void incrementRotation()
    {
        m_rotation++;
    }

    void decrementRotation()
    {
        m_rotation--;
    }

    int getWidth() const
    {
        return m_width;
    }

    int getHeight() const
    {
        return m_height;
    }

    unsigned int getRotation() const
    {
        return m_rotation;
    }

    Color getColor() const
    {
        return m_color;
    }

    bool getElement(int x, int y, unsigned int rotation) const
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

    bool getElement(int x, int y) const
    {
        return getElement(x, y, m_rotation);
    }


    int posX = 0, posY = 0;

protected:
    Tetromino(int width, int height, Color color)
        : m_width(width),
          m_height(height),
          m_color(color)
    {
        int size = width * height;
        m_cells.reserve(size);
        for (int i = 0; i < size; i++)
        {
            m_cells.push_back(false);
        }
    }

    std::vector<bool> m_cells;
    Color m_color = Color::None;
    const int m_width = 3, m_height = 3;
    unsigned int m_rotation = 0;
};

#endif//THREEPP_TETRIS_TETROMINO_HPP
