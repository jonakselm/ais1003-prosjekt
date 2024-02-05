

#ifndef TETRIS_BOARDVIEW_HPP
#define TETRIS_BOARDVIEW_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Board.hpp"
#include "../Tetromino/Tetromino.hpp"


class BoardView
{
public:
    enum class Piece { Current, Next, Hold };

    BoardView(const sf::Vector2i &size);

	void initText(const sf::Vector2i &size);

    // TODO: Make code more efficient
    void updateBoard(const std::array<int, Board::BOARD_SIZE> &boardData);

    void updateTetromino(const Tetromino *const tetroData, Piece piece);

    void setScore(unsigned int score);
    void setLines(unsigned int lines);
    void setLevel(unsigned int level);

	void draw(sf::RenderTarget &target) const;

private:
    // Non const because static
    static sf::Color intToColor(int color);

    void updateBlock(sf::RectangleShape &block, int x, int y, sf::Color color);

    void createBlock(sf::RectangleShape &block, int x, int y, sf::Color color);

    std::array<sf::RectangleShape, Board::HEIGHT> m_border;
    std::array<sf::RectangleShape, Board::BOARD_SIZE> m_board;
	std::array<sf::RectangleShape, 4> m_currentTetromino;
 	std::array<sf::RectangleShape, 4> m_nextTetromino;
    std::array<sf::RectangleShape, 4> m_holdTetromino;

	sf::Font m_font;
	sf::Text m_score, m_lines, m_level, m_next, m_hold;
    static constexpr int NEXT_OFFSET_X = 11, NEXT_OFFSET_Y = 9;
    static constexpr int HOLD_OFFSET_X = 16, HOLD_OFFSET_Y = 9;
    const sf::Vector2i m_gridSize;
};

#endif//TETRIS_BOARDVIEW_HPP
