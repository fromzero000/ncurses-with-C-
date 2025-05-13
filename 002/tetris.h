#ifndef TETRIS_H
#define TETRIS_H

#include <vector>

const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;

struct GameState {
    std::vector<std::vector<char>> board;
    int block_x, block_y;
    bool running;
};

void init_game(GameState& state);

void spawn_new_block(GameState& state);

#endif // TETRIS_H
