#include "GameBoard.hpp"
#include "Utility.hpp"

GameBoard::GameBoard(threepp::Scene &scene)
    :
    m_scene(scene)
{
    /*for (int i = 0; i < m_board.size(); i++)
    {
        if (m_board[i] > 0)
        {
            m_bricks[i] = threepp::createBox({ float(i % m_width), float(i / m_width), 0 }, threepp::Color::green);
        }
    }*/
    int fallingCount = 0;
    for (int y = 0; y < tetromino.getHeight(); y++)
    {
        for (int x = 0; x < tetromino.getWidth(); x++)
        {
            if (tetromino.getElement(x, y))
            {
                m_falling[fallingCount++] = createBox({float(x), float(y), 0}, threepp::Color::green);
            }
        }
    }
}

void GameBoard::addToScene()
{
    for (const auto &brick : m_bricks)
    {
        if (brick.get())
        {
            m_scene.add(brick);
        }
    }
    for (const auto &brick : m_falling)
    {
        m_scene.add(brick);
    }
}

void GameBoard::update(float dt)
{
    m_elapsedTime += dt;
    // Moving down and grounding blocks
    if (m_elapsedTime > m_timeThreshold)
    {
        m_elapsedTime -= m_timeThreshold;
        if (canMove(Direction::Down, tetromino))
        {
            tetromino.posY += 1;
            for (auto &brick : m_falling)
            {
                brick->position.y += 1;
            }
        }
        else
        {
            Board::groundTetromino(tetromino);
            for (auto &brick : m_falling)
            {
                brick->position.y -= tetromino.posY;
            }
            tetromino.posY = 0;
            for (int i = 0; i < m_board.size(); i++)
            {
                if (m_board[i] > 0)
                {
                    m_bricks[i] = createBox({ float(i % m_width), float(i / m_width), 0 }, threepp::Color::green);
                    m_scene.add(m_bricks[i]);
                }
            }
        }
    }
}

void GameBoard::clearLine(int lineNumber)
{
    Board::clearLine(lineNumber);
    // Can't clear line if line isn't full
    if (std::count(Board::m_board.begin(), Board::m_board.end(), 1) == Board::m_width)
    {
        clearLine(lineNumber);
        auto start = m_bricks.begin() + lineNumber * m_width;
        auto end = m_bricks.begin() + (lineNumber + 1) * m_width;
        std::for_each(start, end, [this](std::shared_ptr<threepp::Mesh> &brick)
        {
            m_scene.remove(*brick);
            brick.reset();
        });
        std::rotate(start, end, m_bricks.end());
        std::for_each(m_bricks.begin(), start, [](std::shared_ptr<threepp::Mesh> &brick)
        {
            if (brick.get())
            {
                brick->position.y += 1;
            }
        });
    }
}

void GameBoard::onKeyPressed(threepp::KeyEvent keyEvent)
{
    switch (keyEvent.key)
    {
    case threepp::Key::UP:
        // Instant place down
        break;
    case threepp::Key::DOWN:
        // Fall faster
        //m_timeThreshold = 0.5f;
        break;
    case threepp::Key::LEFT:
        // Go left
        if (canMove(Direction::Left, tetromino))
        {
            for (const auto &brick : m_falling)
            {
                brick->position.x -= 1;
            }
            tetromino.posX -= 1;
        }
        break;
    case threepp::Key::RIGHT:
        // Go Right
        if (canMove(Direction::Right, tetromino))
        {
            for (const auto &brick : m_falling)
            {
                brick->position.x += 1;
            }
            tetromino.posX += 1;
        }
        break;
    case threepp::Key::D:
        // Rotate Left
        tetromino.decrementRotation();
        updateRotation();
        break;
    case threepp::Key::F:
        // Rotate right
        tetromino.incrementRotation();
        updateRotation();
        break;
    }
}

void GameBoard::updateRotation()
{
    int fallingCount = 0;
    for (int y = 0; y < tetromino.getHeight(); y++)
    {
        for (int x = 0; x < tetromino.getWidth(); x++)
        {
            if (tetromino.getElement(x, y))
            {
                m_falling[fallingCount]->position.x = x + tetromino.posX;
                m_falling[fallingCount]->position.y = y + tetromino.posY;
                fallingCount++;
            }
        }
    }
}
