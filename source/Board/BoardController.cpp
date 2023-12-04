#include "BoardController.hpp"


BoardController::BoardController(threepp::GLRenderer &renderer, threepp::Scene &scene)
    : m_view(renderer, scene),
      m_rng(m_rd()),
      m_tetroDist(0, 6)
{
    m_tetromino = randomTetromino();
    m_nextTetromino = randomTetromino();
    m_view.updateTetromino(*m_tetromino, BoardView::Piece::Current);
    m_view.updateTetromino(*m_nextTetromino, BoardView::Piece::Next) ;
}

void BoardController::update(float dt)
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

void BoardController::onKeyPressed(threepp::KeyEvent keyEvent)
{
    // TODO: Make cleaner
    switch (keyEvent.key)
    {
    case threepp::Key::UP:
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
    case threepp::Key::D:
        // Rotate Left
        if (m_board.canDo(Board::Action::RotateLeft, *m_tetromino))
        {
            m_tetromino->rotation--;
            m_view.updateTetromino(*m_tetromino, BoardView::Piece::Current);
        }
        clampXToBoard();
        break;
    case threepp::Key::F:
        // Rotate right
        if (m_board.canDo(Board::Action::RotateRight, *m_tetromino))
        {
            m_tetromino->rotation++;
            m_view.updateTetromino(*m_tetromino, BoardView::Piece::Current);
        }
        clampXToBoard();
        break;
    case threepp::Key::R:
        restart();
        break;
    case threepp::Key::H:
        if (m_canSwap)
        {
            swapHold();
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
        m_timeThreshold = 0.25;
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
    m_view.updateTetromino(*m_tetromino, BoardView::Piece::Current);
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
    m_view.updateTetromino(*m_tetromino, BoardView::Piece::Current);
    m_view.updateTetromino(*m_nextTetromino, BoardView::Piece::Next);
    m_view.updateBoard(board);

    m_canSwap = true;
}

void BoardController::resetTetrominoPos(Tetromino &tetromino)
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
    int i = m_tetroDist(m_rng);

    std::unique_ptr<Tetromino> t;

    switch (i)
    {
    default:
    case 0:
        t = std::make_unique<TetroI>();
        m_i++;
        break;
    case 1:
        t = std::make_unique<TetroO>();
        m_o++;
        break;
    case 2:
        t = std::make_unique<TetroT>();
        m_t++;
        break;
    case 3:
        t = std::make_unique<TetroJ>();
        m_j++;
        break;
    case 4:
        t = std::make_unique<TetroL>();
        m_l++;
        break;
    case 5:
        t = std::make_unique<TetroS>();
        m_s++;
        break;
    case 6:
        t = std::make_unique<TetroZ>();
        m_z++;
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
        m_view.updateTetromino(*m_nextTetromino, BoardView::Piece::Next);
    }
    m_view.updateTetromino(*m_tetromino, BoardView::Piece::Current);
    m_view.updateTetromino(*m_holdTetromino, BoardView::Piece::Hold);

    m_canSwap = false;
}

void BoardController::restart()
{
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
    m_view.updateTetromino(*m_tetromino, BoardView::Piece::Current);
    m_view.updateBoard(m_board.getBoard());
}
