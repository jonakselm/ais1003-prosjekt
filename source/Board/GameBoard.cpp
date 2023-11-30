#include "Board/GameBoard.hpp"
#include "Utility.hpp"

/*GameBoard::GameBoard(threepp::Scene &scene)
    :
    m_scene(scene)
{
    for (int i = 0; i < m_background.size(); i++)
    {
        m_background[i] = createBox({ float(i % WIDTH), float(i / WIDTH), 0 }, threepp::Color::gray);
        m_scene.add(*m_background[i]);
    }
    createTetromino();
}

void GameBoard::update(float dt)
{
    m_elapsedTime += dt;
    // Check if falling piece is out of bounds and reposition it accordingly
    int deltaX = 0;
    for (const auto &brick : m_falling)
    {
        if (brick->position.x < 0)
        {
            deltaX = -brick->position.x;
        }
        else if (brick->position.x > WIDTH)
        {
            deltaX = WIDTH - brick->position.x;
        }
    }
    if (deltaX != 0)
    {
        moveTetromino(deltaX, 0);
    }
    // Moving down and groundTetros::Sizeing blocks
    if (m_elapsedTime > m_timeThreshold)
    {
        m_elapsedTime -= m_timeThreshold;
        if (canDo(Action::MoveDown, *m_currentTetromino))
        {
            moveTetromino(0, 1);
        }
        else
        {
            int flags = Board::groundTetromino(*m_currentTetromino);
            if (flags)
            {
                for (int i = 0; i < HEIGHT; i++)
                {
                    if (flags & 1 << i)
                    {
                        clearLine(i);
                        m_lines++;
                    }
                }
            }
            m_level = std::min(m_lines / 10, 6);
            m_timeThreshold = m_times.at(m_level);
            for (int i = 0; i < m_board.size(); i++)
            {
                // If it exists in board, but haven't been added to bricks yet
                if (m_board[i] > 0 && !m_bricks[i])
                {
                    threepp::Color color = getColorFromIndex(m_currentTetromino->getColor());
                    m_bricks[i] = createBox({ float(i % m_width), float(i / m_width), 0 }, color);
                    m_scene.add(*m_bricks[i]);
                }
            }
            // Reset position since we don't change size of array
           for (auto &brick : m_falling)
            {
                m_scene.remove(*brick);
            }
            m_currentTetromino.reset();
            createTetromino();
        }
    }
}

void GameBoard::clearLine(int lineNumber)
{
    // Can't clear line if line isn't full
    auto start = m_bricks.begin() + lineNumber * m_width;
    auto end = start + m_width;
    // Remove brick from scene
    std::for_each(start, end, [this](std::unique_ptr<threepp::Mesh> &brick)
    {
        if (brick)
        {
            m_scene.remove(*brick);
            brick.reset();
        }
    });
    // Move the rendered bricks to the correct place in the array
    // Effectively move all bricks above go one down
    std::rotate(m_bricks.begin(), start, end);
    // Make all rendered bricks above the cleared line go one down in grid space
    std::for_each(m_bricks.begin(), end, [](std::unique_ptr<threepp::Mesh> &brick)
    {
        if (brick)
        {
            brick->position.y += 1;
        }
    });
}

void GameBoard::onKeyPressed(threepp::KeyEvent keyEvent)
{
    switch (keyEvent.key)
    {
    case threepp::Key::UP:
        // Instant place down
        while (canDo(Action::MoveDown, *m_currentTetromino))
        {
            moveTetromino(0, 1);
        }
        break;
    case threepp::Key::DOWN:
        // Move faster
        m_timeThreshold = 0.05;
        break;
    case threepp::Key::LEFT:
        // Go left
        if (canDo(Action::MoveLeft, *m_currentTetromino))
        {
            moveTetromino(-1, 0);
        }
        break;
    case threepp::Key::RIGHT:
        // Go Right
        if (canDo(Action::MoveRight, *m_currentTetromino))
        {
            moveTetromino(1, 0);
        }
        break;
    case threepp::Key::D:
        // Rotate Left
        if (canDo(Action::RotateLeft, *m_currentTetromino))
        {
            m_currentTetromino->decrementRotation();
            updateRotation();
        }
        break;
    case threepp::Key::F:
        // Rotate right
        if (canDo(Action::RotateRight, *m_currentTetromino))
        {
            m_currentTetromino->incrementRotation();
            updateRotation();
        }
        break;
    }
}

void GameBoard::onKeyReleased(threepp::KeyEvent keyEvent)
{
    switch (keyEvent.key)
    {
        // Set time threshold back to normal
    case threepp::Key::DOWN:
        m_timeThreshold = 0.25;
        break;
    }
}

void GameBoard::onKeyRepeat(threepp::KeyEvent keyEvent)
{
    switch (keyEvent.key)
    {
    case threepp::Key::LEFT:
        // Go left
        if (canDo(Action::MoveLeft, *m_currentTetromino))
        {
            moveTetromino(-1, 0);
        }
        break;
    case threepp::Key::RIGHT:
        // Go Right
        if (canDo(Action::MoveRight, *m_currentTetromino))
        {
            moveTetromino(1, 0);
        }
        break;
    }
}

void GameBoard::createCurrentTetromino()
{
    m_currentTetromino = getTetrominoFromIndex(std::rand() % static_cast<int>(Tetros::Size));
    m_currentTetromino->posX += Board::WIDTH / 2 - m_currentTetromino->getWidth() / 2;
    int fallingCount = 0;
    for (int y = 0; y < m_currentTetromino->getHeight(); y++)
    {
        for (int x = 0; x < m_currentTetromino->getWidth(); x++)
        {
            if (int colorIndex = m_currentTetromino->getElement(x, y))
            {
                std::unique_ptr<threepp::Mesh> &brick = m_falling[fallingCount++];
                brick = createBox({float(x + m_currentTetromino->posX), float(y + m_currentTetromino->posY), 0}, getColorFromIndex(m_currentTetromino->getColor()));
                m_scene.add(*brick);
            }
        }
    }
}

void GameBoard::moveTetromino(int x, int y)
{
    m_currentTetromino->posX += x;
    m_currentTetromino->posY += y;
    for (auto &brick : m_falling)
    {
        brick->position += { static_cast<float>(x), static_cast<float>(y), 0 };
    }
}

void GameBoard::updateRotation()
{
    int fallingCount = 0;
    for (int y = 0; y < m_currentTetromino->getHeight(); y++)
    {
        for (int x = 0; x < m_currentTetromino->getWidth(); x++)
        {
            if (m_currentTetromino->getElement(x, y))
            {
                auto &brick = *m_falling[fallingCount++];
                brick.position.x = x + m_currentTetromino->posX;
                brick.position.y = y + m_currentTetromino->posY;
            }
        }
    }
}

std::unique_ptr<Tetromino> GameBoard::getTetrominoFromIndex(unsigned int index)
{
    switch (static_cast<Tetros>(index))
    {
    default:
    case Tetros::I:
        return std::make_unique<TetroI>();
    case Tetros::O:
        return std::make_unique<TetroO>();
    case Tetros::T:
        return std::make_unique<TetroT>();
    case Tetros::J:
        return std::make_unique<TetroJ>();
    case Tetros::L:
        return std::make_unique<TetroL>();
    case Tetros::S:
        return std::make_unique<TetroS>();
    case Tetros::Z:
        return std::make_unique<TetroZ>();
    }
}

threepp::Color GameBoard::getColorFromIndex(Tetromino::Color index)
{
    switch (index)
    {
    default:
    case Tetromino::Color::Cyan:
        return threepp::Color::cyan;
        break;
    case Tetromino::Color::Yellow:
        return threepp::Color::yellow;
        break;
    case Tetromino::Color::Purple:
        return threepp::Color::purple;
        break;
    case Tetromino::Color::Blue:
        return threepp::Color::blue;
        break;
    case Tetromino::Color::Orange:
        return threepp::Color::orange;
        break;
    case Tetromino::Color::Green:
        return threepp::Color(0, 255, 0);
        break;
    case Tetromino::Color::Red:
        return threepp::Color::red;
        break;
    }
}
*/