

#ifndef TETRIS_BOARDCONTROLLER_HPP
#define TETRIS_BOARDCONTROLLER_HPP

#include "BoardView.hpp"
#include <random>
#include <memory>
#include <iostream>

class BoardController
{
public:
	enum class FingerDirection { None, Vertical, Horizontal };

    BoardController(const sf::Vector2i &size);

    void update(sf::Time dt);

	void draw(sf::RenderTarget &target) const;

private:
	void handleInput(sf::Time dt);
    void moveTetromino(int x, int y);
    void groundTetromino();
    void resetTetrominoPos(Tetromino &tetromino) const;
    void clampXToBoard();
    std::unique_ptr<Tetromino> randomTetromino();

    void swapHold();
    void restart();
    void moveDownIfPossible();

	sf::Vector2i m_screenSize;

    BoardView m_view;
    Board m_board;
    std::unique_ptr<Tetromino> m_tetromino;
    std::unique_ptr<Tetromino> m_nextTetromino;
    std::unique_ptr<Tetromino> m_holdTetromino;

	sf::Time m_timeThreshold = sf::milliseconds(500);
	sf::Time m_elapsedTime = sf::Time::Zero;
    unsigned int m_score = 0;
    int m_lines = 0;
    int m_level = 0;
    std::array<sf::Time, 7> m_times = { sf::milliseconds(500),
		sf::milliseconds(400), sf::milliseconds(300), sf::milliseconds(250),
		sf::milliseconds(200), sf::milliseconds(150), sf::milliseconds(100) };
    bool m_swappable = true;
    bool m_pauseToggleable = true;
    bool m_pause = false;
	bool m_spacePressed = false;
	bool m_leftPressed = false;
	bool m_rightPressed = false;
	bool m_zPressed = false;
	bool m_upPressed = false;
	bool m_rPressed = false;

    std::random_device m_rd;
    std::mt19937 m_rng;
    std::uniform_int_distribution<int> m_tetroDist;

    int m_i = 0, m_o = 0, m_t = 0, m_j = 0, m_l = 0, m_s = 0, m_z = 0;

    sf::Vector2i m_fingerRefPoint;
	int m_fingerMoveThreshold = 30;
	bool m_refIsSet = false;
	FingerDirection m_fingerDir = FingerDirection::None;
	sf::Time m_timeTouched = sf::Time::Zero;
	const sf::Time m_rotationTimeThreshold = sf::milliseconds(500);
	bool m_fingerWasDown = false;
};

#endif//TETRIS_BOARDCONTROLLER_HPP
