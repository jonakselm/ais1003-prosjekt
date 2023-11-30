#include "BoardView.hpp"
#include "Utility.hpp"

BoardView::BoardView(threepp::GLRenderer& renderer, threepp::Scene& scene)
    : m_renderer(renderer),
      m_scene(scene),
      m_score(m_renderer.textHandle("Score: 0")),
      m_lines(m_renderer.textHandle("Lines: 0")),
      m_level(m_renderer.textHandle("Level: 0")),
      m_next(m_renderer.textHandle("Next:")),
      m_hold(m_renderer.textHandle("Hold:"))
{
    for (int i = 0; i < m_background.size(); i++)
    {
        m_background[i] = createBox({ float(i % Board::WIDTH), float(i / Board::WIDTH), 0 }, threepp::Color::gray);
        m_scene.add(*m_background[i]);
    }
    m_score.scale = 2;
    m_score.setPosition(325, 10);
    m_lines.scale = 2;
    m_lines.setPosition(325, 50);
    m_level.scale = 2;
    m_level.setPosition(325, 90);
    m_next.scale = 2;
    m_next.setPosition(325, 150);
    m_hold.scale = 2;
    m_hold.setPosition(500, 150);
}

void BoardView::updateBoard(const std::array<int, Board::BOARD_SIZE> & boardData)
{
    // Remove old
    for (auto &block : m_board)
    {
        if (block)
        {
            m_scene.remove(*block);
            block.reset();
        }
    }
    // Add new
    for (int i = 0; i < boardData.size(); i++)
    {
        if (boardData[i])
        {
            m_board[i] = createBox({  float(i % Board::WIDTH), float(i / Board::WIDTH), 0 }, intToColor(boardData[i]));
            m_scene.add(*m_board[i]);
        }
    }
}

// TODO: Make function a lot dumber
void BoardView::updateTetromino(const Tetromino &tetroData, Piece piece)
{
    VisualTetromino *tetroPtr = nullptr;

    int offsetX = 0;
    int offsetY = 0;
    unsigned int rotation = 0;

    switch (piece)
    {
    default:
    case Piece::Current:
        tetroPtr = &m_currentTetromino;
        offsetX = tetroData.posX;
        offsetY = tetroData.posY;
        rotation = tetroData.getRotation();
        break;
    case Piece::Next:
        tetroPtr = &m_nextTetromino;
        offsetX = NEXT_OFFSET_X;
        offsetY = NEXT_OFFSET_Y;
        rotation = 0;
        break;
    case Piece::Hold:
        tetroPtr = &m_holdTetromino;
        offsetX = HOLD_OFFSET_X;
        offsetY = HOLD_OFFSET_Y;
        rotation = 0;
        break;
    }

    bool willCreate = false;
    for (const auto &block : *tetroPtr)
    {
        if (!block)
        {
            willCreate = true;
        }
    }


    int tetroBlock = 0;
    for (int y = 0; y < tetroData.getHeight(); y++)
    {
        for (int x = 0; x < tetroData.getWidth(); x++)
        {
            if (int colorData = tetroData.getElement(x, y, rotation))
            {
                auto &block = (*tetroPtr)[tetroBlock++];
                if (block)
                {
                    updateBlock(block, x + offsetX, y + offsetY, intToColor(colorData));
                }
                else
                {
                    createBlock(block, x + offsetX, y + offsetY, intToColor(colorData));
                }
            }
        }
    }
}

void BoardView::setScore(unsigned int score)
{
    m_score.setText("Score: " + std::to_string(score));
}

void BoardView::setLines(unsigned int lines)
{
    m_lines.setText("Lines: " + std::to_string(lines));
}

void BoardView::setLevel(unsigned int level)
{
    m_level.setText("Level: " + std::to_string(level));
}

threepp::Color BoardView::intToColor(int color)
{
    switch (color)
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

void BoardView::updateBlock(TetroBlock& block, int x, int y, threepp::Color color)
{
    block->position = { static_cast<float>(x), static_cast<float>(y), 0 };
    auto material = threepp::MeshBasicMaterial::create();
    material->color = color;
    block->setMaterial(material);
}

void BoardView::createBlock(TetroBlock& block, int x, int y, threepp::Color color)
{
    block = createBox({static_cast<float>(x), static_cast<float>(y), 0}, color);
    m_scene.add(*block);
}
