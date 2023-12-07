

#ifndef TETRIS_BOARDCONTROLLER_HPP
#define TETRIS_BOARDCONTROLLER_HPP

#include "BoardView.hpp"
#include <random>
#include <iostream>

class BoardController : public threepp::KeyListener
{
public:
    BoardController(threepp::GLRenderer &renderer, threepp::Scene &scene, const threepp::WindowSize &size);

    void onWindowResize(const threepp::WindowSize &size);

    void update(float dt);

    void onKeyPressed(threepp::KeyEvent keyEvent) override;
    void onKeyReleased(threepp::KeyEvent keyEvent) override;
    void onKeyRepeat(threepp::KeyEvent keyEvent) override;

private:
    void moveTetromino(int x, int y);
    void groundTetromino();
    void resetTetrominoPos(Tetromino &tetromino) const;
    void clampXToBoard();
    std::unique_ptr<Tetromino> randomTetromino();

    void swapHold();
    void restart();


    BoardView m_view;
    Board m_board;
    std::unique_ptr<Tetromino> m_tetromino;
    std::unique_ptr<Tetromino> m_nextTetromino;
    std::unique_ptr<Tetromino> m_holdTetromino;

    float m_timeThreshold = 0.5f;
    float m_elapsedTime = 0;
    unsigned int m_score = 0;
    int m_lines = 0;
    int m_level = 0;
    std::array<float, 7> m_times = { 0.5f, 0.4f, 0.3f, 0.25f,
                                    0.2f, 0.15f, 0.1f };
    bool m_canSwap = true;

    std::random_device m_rd;
    std::mt19937 m_rng;
    std::uniform_int_distribution<int> m_tetroDist;

    int m_i = 0, m_o = 0, m_t = 0, m_j = 0, m_l = 0, m_s = 0, m_z = 0;
};

#endif//TETRIS_BOARDCONTROLLER_HPP
