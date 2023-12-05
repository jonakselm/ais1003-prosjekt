

#ifndef TETRIS_BOARDVIEW_HPP
#define TETRIS_BOARDVIEW_HPP

#include "threepp/threepp.hpp"
#include "Board.hpp"
#include "Tetromino/Tetromino.hpp"

typedef std::unique_ptr<threepp::Mesh> TetroBlock;
typedef std::array<TetroBlock, 4> VisualTetromino;

class BoardView
{
public:
    enum class Piece { Current, Next, Hold };

    BoardView(threepp::GLRenderer &renderer, threepp::Scene &scene, const threepp::WindowSize &size);

    void onWindowResize(const threepp::WindowSize &size);

    // TODO: Make code more efficient
    void updateBoard(const std::array<int, Board::BOARD_SIZE> &boardData);

    void updateTetromino(const Tetromino &tetroData, Piece piece);

    void setScore(unsigned int score);
    void setLines(unsigned int lines);
    void setLevel(unsigned int level);

private:
    static threepp::Color intToColor(int color);

    void updateBlock(TetroBlock &block, int x, int y, threepp::Color color);

    void createBlock(TetroBlock &block, int x, int y, threepp::Color color);


    threepp::GLRenderer &m_renderer;
    threepp::Scene &m_scene;

    std::array<TetroBlock, Board::HEIGHT> m_border;
    std::array<TetroBlock, Board::BOARD_SIZE> m_board;
    VisualTetromino m_currentTetromino;
    VisualTetromino m_nextTetromino;
    VisualTetromino m_holdTetromino;

    threepp::TextHandle &m_score, &m_lines, &m_level, &m_next, &m_hold;
    static constexpr int NEXT_OFFSET_X = 11, NEXT_OFFSET_Y = 9;
    static constexpr int HOLD_OFFSET_X = 16, HOLD_OFFSET_Y = 9;
};

#endif//TETRIS_BOARDVIEW_HPP
