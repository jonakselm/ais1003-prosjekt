#ifndef THREEPP_TETRIS_GAMEBOARD_HPP
#define THREEPP_TETRIS_GAMEBOARD_HPP

#include "Board.hpp"
#include "Tetromino.hpp"
#include "Utility.hpp"
#include "threepp/threepp.hpp"

class GameBoard : public Board, public threepp::KeyListener
{
public:
    GameBoard(threepp::Scene &scene);

    void addToScene();

    void update(float dt) override;

    void clearLine(int lineNumber) override;

private:
    void onKeyPressed(threepp::KeyEvent keyEvent) override;

    void updateRotation();

private:
    threepp::Scene &m_scene;
    std::array<std::shared_ptr<threepp::Mesh>, BOARD_SIZE> m_bricks;
    Tetromino tetromino;
    std::array<std::shared_ptr<threepp::Mesh>, 4> m_falling;
    float m_elapsedTime = 0;
    float m_timeThreshold = 1;
};

#endif//THREEPP_TETRIS_GAMEBOARD_HPP
