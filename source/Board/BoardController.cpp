#include "BoardController.hpp"
#include "TetrominoPieces.hpp"


BoardController::BoardController(threepp::GLRenderer &renderer, threepp::Scene &scene, const threepp::WindowSize &size)
    : m_view(renderer, scene, size),
      m_rng(m_rd()),
      m_tetroDist(0, 6)
{
    m_tetromino = randomTetromino();
    m_nextTetromino = randomTetromino();
    m_view.updateTetromino(m_tetromino.get(), BoardView::Piece::Current);
    m_view.updateTetromino(m_nextTetromino.get(), BoardView::Piece::Next) ;
}

void BoardController::onWindowResize(const threepp::WindowSize& size)
{
    m_view.onWindowResize(size);
}

void BoardController::update(float dt)
{
    if (!m_pause)
    {
        m_elapsedTime += dt;
        // Check if falling piece is out of bounds and reposition it accordingly
        // Moving down and grounding blocks
        if (m_elapsedTime > m_timeThreshold)
        {
            m_elapsedTime -= m_timeThreshold;
            if (m_board.canDo(Board::Action::MoveDown, *m_tetromino))
            {
                moveTetromino(0, 1);
            }
            else
            {
                if (m_tetromino->posY <= 0)
                {
                    restart();
                }
                else
                {
                    groundTetromino();
                }
            }
        }
    }
}

void BoardController::onKeyPressed(threepp::KeyEvent keyEvent)
{
    // TODO: Make cleaner
    switch (keyEvent.key)
    {
    case threepp::Key::SPACE:
        // Instant place down
        while (m_board.canDo(Board::Action::MoveDown, *m_tetromino))
        {
            moveTetromino(0, 1);
        }
        groundTetromino();
        break;
    case threepp::Key::DOWN:
        // Move faster
        m_timeThreshold = 0.05;
        break;
    case threepp::Key::LEFT:
        // Go left
        if (m_board.canDo(Board::Action::MoveLeft, *m_tetromino))
        {
            moveTetromino(-1, 0);
        }
        break;
    case threepp::Key::RIGHT:
        // Go Right
        if (m_board.canDo(Board::Action::MoveRight, *m_tetromino))
        {
            moveTetromino(1, 0);
        }
        break;
    case threepp::Key::Z:
        // Rotate Left
        if (m_board.canDo(Board::Action::RotateLeft, *m_tetromino))
        {
            m_tetromino->rotation--;
            m_view.updateTetromino(m_tetromino.get(), BoardView::Piece::Current);
        }
        clampXToBoard();
        break;
    case threepp::Key::UP:
        // Rotate right
        if (m_board.canDo(Board::Action::RotateRight, *m_tetromino))
        {
            m_tetromino->rotation++;
            m_view.updateTetromino(m_tetromino.get(), BoardView::Piece::Current);
        }
        clampXToBoard();
        break;
    case threepp::Key::R:
        restart();
        break;
    case threepp::Key::C:
        if (m_swappable)
        {
            swapHold();
        }
        break;
    case threepp::Key::P:
        if (m_pauseToggleable && !m_pause)
        {
            m_pause = true;
            m_pauseToggleable = false;
        }
        else
        {
            m_pauseToggleable = true;
        }
        break;
    }
}

void BoardController::onKeyReleased(threepp::KeyEvent keyEvent)
{
    switch (keyEvent.key)
    {
        // Set time threshold back to normal
    case threepp::Key::DOWN:
        m_timeThreshold = m_times[m_level];
        break;
    case threepp::Key::P:
        if (m_pauseToggleable && m_pause)
        {
            m_pause = false;
        }
        else
        {
            m_pauseToggleable = true;
        }
        break;
    }
}

void BoardController::onKeyRepeat(threepp::KeyEvent keyEvent)
{
    switch (keyEvent.key)
    {
    case threepp::Key::LEFT:
        // Go left
        if (m_board.canDo(Board::Action::MoveLeft, *m_tetromino))
        {
            moveTetromino(-1, 0);
        }
        break;
    case threepp::Key::RIGHT:
        // Go Right
        if (m_board.canDo(Board::Action::MoveRight, *m_tetromino))
        {
            moveTetromino(1, 0);
        }
        break;
    }
}

void BoardController::moveTetromino(int x, int y)
{
    m_tetromino->posX += x;
    m_tetromino->posY += y;
    m_view.updateTetromino(m_tetromino.get(), BoardView::Piece::Current);
}

void BoardController::groundTetromino()
{
    const auto &board = m_board.getBoard();
    int flags = m_board.groundTetromino(*m_tetromino);
    m_score += 25;
    int prevLines = m_lines;
    if (flags)
    {
        for (int i = 0; i < Board::HEIGHT; i++)
        {
            if (flags & 1 << i)
            {
                m_board.clearLine(i);
                m_lines++;
            }
        }
        // Increase by 100 * powers of 2 depending on the amount of lines cleared
        m_score += (1 << (m_lines - prevLines)) * 100;
        m_level = std::min(m_lines / 10, static_cast<int>(m_times.size() - 1));
        m_timeThreshold = m_times.at(m_level);

        m_view.updateBoard(m_board.getBoard());
        m_view.setLevel(m_level);
        m_view.setLines(m_lines);
    }
    m_tetromino = std::move(m_nextTetromino);
    m_nextTetromino = randomTetromino();

    m_view.setScore(m_score);
    m_view.updateTetromino(m_tetromino.get(), BoardView::Piece::Current);
    m_view.updateTetromino(m_nextTetromino.get(), BoardView::Piece::Next);
    m_view.updateBoard(board);

    m_swappable = true;
}

void BoardController::resetTetrominoPos(Tetromino &tetromino) const
{
    tetromino.posX = (Board::WIDTH - tetromino.getWidth()) / 2;
    tetromino.posY = -1;
}

void BoardController::clampXToBoard()
{
    int deltaX = 0;
    for (int y = 0; y < m_tetromino->getHeight(); y++)
    {
        for (int x = 0; x < m_tetromino->getWidth(); x++)
        {
            if (m_tetromino->getElement(x, y))
            {
                int posX = m_tetromino->posX + x;
                if (posX < 0)
                {
                    deltaX = -posX;
                }
                else if (posX >= Board::WIDTH)
                {
                    deltaX = Board::WIDTH - posX - 1;
                }
            }
        }
    }
    if (deltaX != 0)
    {
        moveTetromino(deltaX, 0);
    }
}

std::unique_ptr<Tetromino> BoardController::randomTetromino()
{
    // This prevents the function from being const
    int i = m_tetroDist(m_rng);

    std::unique_ptr<Tetromino> t;

    switch (i)
    {
    case 0:
        t = std::make_unique<TetroI>();
        break;
    case 1:
        t = std::make_unique<TetroO>();
        break;
    case 2:
        t = std::make_unique<TetroT>();
        break;
    case 3:
        t = std::make_unique<TetroJ>();
        break;
    case 4:
        t = std::make_unique<TetroL>();
        break;
    case 5:
        t = std::make_unique<TetroS>();
        break;
    case 6:
        t = std::make_unique<TetroZ>();
        break;
    }
    resetTetrominoPos(*t);

    return t;
}

void BoardController::swapHold()
{
    resetTetrominoPos(*m_tetromino);
    m_tetromino->rotation = 0;
    m_tetromino.swap(m_holdTetromino);
    if (!m_tetromino)
    {
        m_tetromino.swap(m_nextTetromino);
        m_nextTetromino = randomTetromino();
        m_view.updateTetromino(m_nextTetromino.get(), BoardView::Piece::Next);
    }
    m_view.updateTetromino(m_tetromino.get(), BoardView::Piece::Current);
    m_view.updateTetromino(m_holdTetromino.get(), BoardView::Piece::Hold);

    m_swappable = false;
}

void BoardController::restart()
{
    m_timeThreshold = m_times[m_level];
    m_tetromino = randomTetromino();
    m_nextTetromino = randomTetromino();
    m_holdTetromino.reset();
    m_board.resetBoard();
    m_score = 0;
    m_lines = 0;
    m_level = 0;
    m_view.setScore(m_score);
    m_view.setLines(m_lines);
    m_view.setLevel(m_level);
    m_view.updateTetromino(m_tetromino.get(), BoardView::Piece::Current);
    m_view.updateTetromino(m_nextTetromino.get(), BoardView::Piece::Next);
    m_view.updateTetromino(m_holdTetromino.get(), BoardView::Piece::Hold);
    m_view.updateBoard(m_board.getBoard());
}
