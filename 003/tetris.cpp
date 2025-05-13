#include "tetris.h"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

void init_game(GameState& state) {
    //srand(888);  // for testing
    srand(time(NULL));
    state.board = std::vector<std::vector<char>>(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, '.'));
    state.current_block = std::vector<std::vector<int>>(4, std::vector<int>(4, 0));
    state.tetrominoes = {
        // I-tetromino (2 rotations)
        {
            {
                {0, 0, 0, 0},
                {1, 1, 1, 1},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            },
            {
                {0, 0, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0},
                {0, 0, 1, 0}
            }
        },
        // O-tetromino (1 rotation)
        {
            {
                {0, 1, 1, 0},
                {0, 1, 1, 0},
                {0, 0, 0, 0},
                {0, 0, 0, 0}
            }
        },
    };
    
    state.current_tetromino = 0;
    state.current_rotation = 0;
    state.block_x = 0;
    state.block_y = 0;
    state.score = 0;
    state.level = 1;
    state.lines_cleared = 0;
//    state.high_score = 0;
    state.running = true;
    state.next_tetromino = rand() % state.tetrominoes.size();
    state.fall_timer = 0;
    state.fall_interval = 10 - (state.level - 1);
    if (state.fall_interval < 1) state.fall_interval = 1;
    spawn_new_block(state);
}


void handle_game_action(GameState& state, int action) {
    switch (action) {
        case ACTION_QUIT:
            state.running = false;
            break;
        case ACTION_LEFT:
            move_block(state, -1, 0);
            break;
        case ACTION_RIGHT:
            move_block(state, 1, 0);
            break;
        case ACTION_DOWN:
            move_block(state, 0, 1);
            break;
        // case ACTION_ROTATE:
        //     rotate_block(state);
            break;
        case ACTION_DROP:
            drop_block_to_bottom(state);
            break;
        default:
            break;
    }
}

bool is_valid_position(const std::vector<std::vector<int>>& block, int x, int y, const std::vector<std::vector<char>>& board){
    for(int i = 0; i < 4; i++){
        int block_y = y+i;
        for(int j = 0; j < 4; j++){
            int block_x = x+j;
            if(block[i][j] == 1){
                if(block_y < 0 || block_y > BOARD_HEIGHT-1
                        || block_x < 0 || block_x > BOARD_WIDTH-1
                        || board[block_y][block_x] == '#') return false;
            }
        }
    }
    return true;
}

void update_game(GameState& state) {
    if (++state.fall_timer >= state.fall_interval) {
        // move block
        // check landing
        move_block(state, 0, 1);
        state.fall_timer = 0;
        state.fall_interval = 10 - (state.level - 1);
        if (state.fall_interval < 1) state.fall_interval = 1;
    }
}

void land_block(GameState& state){
    for(int i = 0; i < 4; i++){
        int y = state.block_y+i;
        for(int j = 0; j < 4; j++){
            int x = state.block_x+j;
            if(state.current_block[i][j] == 1){
                state.board[y][x] = '#';
            }
        }
    }
}

bool move_block(GameState& state, int dx, int dy) {
    int temp_x = state.block_x+dx;
    int temp_y = state.block_y+dy;

    if(is_valid_position(state.current_block, temp_x, temp_y, state.board)){
        state.block_x = temp_x;
        state.block_y = temp_y;
        return true;
    }
    else {
        if(dx == 0 && dy == 1){
            land_block(state);
            spawn_new_block(state);
        }
        return false;
    }
}

void drop_block_to_bottom(GameState& state) {
    while(move_block(state, 0, 1));
}

void spawn_new_block(GameState& state) {
    state.block_x = BOARD_WIDTH/2-2;
    state.block_y = 0;
    state.current_tetromino = state.next_tetromino;
    state.current_rotation = 0;
    state.current_block = state.tetrominoes[state.current_tetromino][state.current_rotation];
    state.next_tetromino = rand()%state.tetrominoes.size();
    if(!is_valid_position(state.current_block,state.block_x,state.block_y,state.board))
        state.running = false;
}



