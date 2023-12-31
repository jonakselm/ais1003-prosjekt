#include "BoardView.hpp"
#include "Utility.hpp"

BoardView::BoardView(threepp::GLRenderer &renderer, threepp::Scene &scene, const threepp::WindowSize &size)
    : m_renderer(renderer),
      m_scene(scene),
      m_scoreText(m_renderer.textHandle("Score: 0")),
      m_lineText(m_renderer.textHandle("Lines: 0")),
      m_levelText(m_renderer.textHandle("Level: 1")),
      m_nextText(m_renderer.textHandle("Next:")),
      m_holdText(m_renderer.textHandle("Hold:"))
{
    for (int i = 0; i < m_border.size(); i++)
    {
        m_border[i] = createBox({ static_cast<float>(Board::WIDTH), static_cast<float>(i) }, threepp::Color::gray);
        m_scene.add(*m_border[i]);
    }
    // Set text position
    onWindowResize(size);
}

void BoardView::onWindowResize(const threepp::WindowSize &size)
{
    m_scoreText.scale = size.height / 200;
    m_scoreText.setPosition(size.width * 0.56, size.height * 0.02);
    m_lineText.scale = size.height / 200;
    m_lineText.setPosition(size.width * 0.56, size.height * 0.1);
    m_levelText.scale = size.height / 200;
    m_levelText.setPosition(size.width * 0.56, size.height * 0.18);
    m_nextText.scale = size.height / 200;
    m_nextText.setPosition(size.width * 0.56, size.height * 0.34);
    m_holdText.scale = size.height / 200;
    m_holdText.setPosition(size.width * 0.82, size.height * 0.34);
}

void BoardView::updateBoard(const std::array<int, Board::BOARD_SIZE> &boardData)
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
            m_board[i] = createBox({  float(i % Board::WIDTH), float(i / Board::WIDTH) }, intToColor(boardData[i]));
            m_scene.add(*m_board[i]);
        }
    }
}

void BoardView::updateTetromino(const Tetromino *const tetroData, Piece piece)
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
        offsetX = tetroData->posX;
        offsetY = tetroData->posY;
        rotation = tetroData->rotation;
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

    if (tetroData)
    {
        int tetroBlock = 0;
        for (int y = 0; y < tetroData->getHeight(); y++)
        {
            for (int x = 0; x < tetroData->getWidth(); x++)
            {
                if (int colorData = tetroData->getElement(x, y, rotation))
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
    else
    {
        for (auto &block : *tetroPtr)
        {
            m_scene.remove(*block);
            block.reset();
        }
    }
}

void BoardView::setScore(unsigned int score)
{
    m_scoreText.setText("Score: " + std::to_string(score));
}

void BoardView::setLines(unsigned int lines)
{
    m_lineText.setText("Lines: " + std::to_string(lines));
}

void BoardView::setLevel(unsigned int level)
{
    // Add 1 because it is also used for indexing an array
    m_levelText.setText("Level: " + std::to_string(level + 1));
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

void BoardView::updateBlock(TetroBlock &block, int x, int y, threepp::Color color)
{
    block->position = { static_cast<float>(x), static_cast<float>(y), 0 };
    auto material = threepp::MeshBasicMaterial::create();
    material->color = color;
    block->setMaterial(material);
}

void BoardView::createBlock(TetroBlock &block, int x, int y, threepp::Color color)
{
    block = createBox({static_cast<float>(x), static_cast<float>(y)}, color);
    m_scene.add(*block);
}
