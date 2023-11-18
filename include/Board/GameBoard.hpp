#ifndef THREEPP_TETRIS_GAMEBOARD_HPP
#define THREEPP_TETRIS_GAMEBOARD_HPP

#include "Board.hpp"
#include "Tetromino/TetrominoPieces.hpp"
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
    enum class Tetros { I, O, T, J, L, S, Z, Size };

    void onKeyPressed(threepp::KeyEvent keyEvent) override;
    void onKeyReleased(threepp::KeyEvent keyEvent) override;
    void onKeyRepeat(threepp::KeyEvent keyEvent) override;

    void updateRotation();

    void updateTetromino();

    void moveTetromino(int x, int y);

    threepp::Color getColorFromIndex(Tetromino::Color index);

    std::unique_ptr<Tetromino> getTetrominoFromIndex(unsigned int index);


    threepp::Scene &m_scene;
    std::array<std::unique_ptr<threepp::Mesh>, BOARD_SIZE> m_background;
    // 0 - 9 is top row, while back() etc. is bottom row
    std::array<std::unique_ptr<threepp::Mesh>, BOARD_SIZE> m_bricks;
    std::unique_ptr<Tetromino> m_tetromino;
    std::array<std::unique_ptr<threepp::Mesh>, 4> m_falling;
    float m_elapsedTime = 0;
    float m_timeThreshold = 0.25;
};

#endif//THREEPP_TETRIS_GAMEBOARD_HPP
