#include "BoardView.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

BoardView::BoardView()
{
    for (int i = 0; i < m_border.size(); i++)
    {
		auto &rect = m_border[i];
		rect.setSize({ 30, 30 });
		rect.setPosition({ static_cast<float>(Board::WIDTH) * 30, static_cast<float>(i) * 30 });
		rect.setFillColor(sf::Color(128, 128, 128));
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(-1);
	}
	for (int i = 0; i < m_board.size(); i++)
	{
		auto &rect = m_board[i];
		rect.setSize({ 30, 30 });
		rect.setPosition({ static_cast<float>(i % Board::WIDTH) * 30, static_cast<float>(i / Board::WIDTH) * 30 });
		rect.setFillColor(sf::Color::Black);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(-1);
	}
	for (auto &rect : m_currentTetromino)
	{
		rect.setSize({ 30, 30 });
		rect.setFillColor(sf::Color::Black);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(-1);
	}
	for (auto &rect : m_holdTetromino)
	{
		rect.setSize({ 30, 30 });
		rect.setFillColor(sf::Color::Black);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(-1);
	}
	for (auto &rect : m_nextTetromino)
	{
		rect.setSize({ 30, 30 });
		rect.setFillColor(sf::Color::Black);
		rect.setOutlineColor(sf::Color::Black);
		rect.setOutlineThickness(-1);
	}
	if (!m_font.loadFromFile("../DejaVuSans.ttf"))
	{
		exit(-1);
	}
	m_score.setFont(m_font);
	setScore(0);
	m_lines.setFont(m_font);
	setLines(0);
	m_level.setFont(m_font);
	setLevel(0);
	m_next.setFont(m_font);
	m_next.setString("Next");
	m_hold.setFont(m_font);
	m_hold.setString("Hold");
	initText({ 600, 600 });
}

void BoardView::initText(const sf::Vector2i &size)
{
    m_score.setPosition(size.x * 0.56, size.y * 0.02);
    m_score.setCharacterSize(30);
    m_lines.setPosition(size.x * 0.56, size.y * 0.1);
    m_lines.setCharacterSize(30);
    m_level.setPosition(size.x * 0.56, size.y * 0.18);
    m_level.setCharacterSize(30);
    m_next.setPosition(size.x * 0.56, size.y * 0.34);
    m_next.setCharacterSize(30);
    m_hold.setPosition(size.x * 0.82, size.y * 0.34);
    m_hold.setCharacterSize(30);
}

void BoardView::updateBoard(const std::array<int, Board::BOARD_SIZE> &boardData)
{
    for (int i = 0; i < boardData.size(); i++)
    {
        if (boardData[i])
        {
            m_board[i].setPosition({  float(i % Board::WIDTH) * 30, float(i / Board::WIDTH) * 30 });
			m_board[i].setFillColor(intToColor(boardData[i]));
        }
		else
		{
			m_board[i].setFillColor(sf::Color::Black);
		}
    }
}

void BoardView::updateTetromino(const Tetromino *const tetroData, Piece piece)
{
	std::array<sf::RectangleShape, 4> *tetroPtr = nullptr;

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
					float posX = static_cast<float>(x + offsetX) * 30;
					float posY = static_cast<float>(y + offsetY) * 30;
					updateBlock((*tetroPtr)[tetroBlock++], posX, posY, intToColor(colorData));
                }
            }
        }
    }
    else
    {
        for (auto &block : *tetroPtr)
        {
			block.setFillColor(sf::Color::Black);
        }
    }
}

void BoardView::setScore(unsigned int score)
{
    m_score.setString("Score: " + std::to_string(score));
}

void BoardView::setLines(unsigned int lines)
{
    m_lines.setString("Lines: " + std::to_string(lines));
}

void BoardView::setLevel(unsigned int level)
{
    // Add 1 because it is also used for indexing an array
    m_level.setString("Level: " + std::to_string(level + 1));
}

void BoardView::draw(sf::RenderTarget &target) const
{
	for (const auto& rect : m_holdTetromino)
	{
		target.draw(rect);
	}
	for (const auto& rect : m_nextTetromino)
	{
		target.draw(rect);
	}
	for (const auto& rect : m_border)
	{
		target.draw(rect);
	}
	for (const auto& rect : m_board)
	{
		target.draw(rect);
	}
	for (const auto& rect : m_currentTetromino)
	{
		target.draw(rect);
	}
	target.draw(m_hold);
	target.draw(m_next);
	target.draw(m_score);
	target.draw(m_lines);
	target.draw(m_level);
}

sf::Color BoardView::intToColor(int color)
{
    switch (color)
    {
    default:
    case Tetromino::Color::Cyan:
        return sf::Color::Cyan;
        break;
    case Tetromino::Color::Yellow:
        return sf::Color::Yellow;
        break;
    case Tetromino::Color::Purple:
		return sf::Color(128, 0, 128);
        break;
    case Tetromino::Color::Blue:
		return sf::Color::Blue;
        break;
    case Tetromino::Color::Orange:
		return sf::Color(255, 127, 0);
        break;
    case Tetromino::Color::Green:
		return sf::Color::Green;
        break;
    case Tetromino::Color::Red:
		return sf::Color::Red;
        break;
    }
}

void BoardView::updateBlock(sf::RectangleShape &block, int x, int y, sf::Color color)
{
	block.setPosition({ static_cast<float>(x), static_cast<float>(y) });
	block.setFillColor(color);
}

void BoardView::createBlock(sf::RectangleShape &block, int x, int y, sf::Color color)
{
}
