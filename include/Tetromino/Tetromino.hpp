

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
    enum Color { None, Cyan, Yellow, Purple, Blue, Orange, Green, Red };


    int getWidth() const;

    int getHeight() const;

    int getElement(int x, int y, unsigned int rotation) const;

    int getElement(int x, int y) const;


    int posX = 0, posY = 0;
    unsigned int rotation = 0;

protected:
    Tetromino(int width, int height);

    std::vector<int> m_cells;
    const int m_width = 3, m_height = 3;
};

#endif//THREEPP_TETRIS_TETROMINO_HPP
