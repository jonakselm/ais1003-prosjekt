

#ifndef THREEPP_VCPKG_DEMO_TETROMINO_HPP
#define THREEPP_VCPKG_DEMO_TETROMINO_HPP

#include <array>
#include <algorithm>

/* Took inspiration for the brick indexing from
 * Javidx9 on youtube
 * 4x4
 * Rotation 0: m_bricks[x + m_width * y]
 * Rotation 1: m_bricks[12 - x * m_width + y]
 * Rotation 2: m_bricks[15 - x - y * m_width]
 * Rotation 3: m_bricks[3 + m_width * x - y]
 *
 * General
 * Rotation 0: m_bricks[x + m_width * y]
 * Rotation 1: m_bricks[(height-1)* m_width - x * m_width + y]
 * Rotation 2: m_bricks[height * m_width - 1 - x - y * m_width]
 * Rotation 3: m_bricks[m_width - 1 + x * m_width - y]
 *
 * 3x3
 * Rotation 0: m_bricks[x+m_width*y]
 * Rotation 1: m_bricks[6 - x * m_width + y]
 * Rotation 2: m_bricks[8 - x - y * m_width]
 * Rotation 3: m_bricks[2 + x * m_width - y]
 */

class Tetromino
{
public:
    Tetromino()
     : m_bricks({ 0 })
    {
        m_bricks[1] = true;
        m_bricks[3] = true;
        m_bricks[4] = true;
        m_bricks[5] = true;
    }

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

    bool getElement(int x, int y) const
    {
        switch (m_rotation)
        {
            case 0:
                return m_bricks[x+ m_width *y];
                break;
            case 1:
                return m_bricks[6 - x * m_width + y];
                break;
            case 2:
                return m_bricks[8 - x - y * m_width];
                break;
            case 3:
                return m_bricks[2 + x * m_width - y];
                break;
        }
        return false;
    }

public:
    int posX = 0, posY = 0;

private:
    std::array<bool, 9> m_bricks;
    int m_width = 3, m_height = 3;
    int m_rotation = 0;
};

#endif//THREEPP_VCPKG_DEMO_TETROMINO_HPP
