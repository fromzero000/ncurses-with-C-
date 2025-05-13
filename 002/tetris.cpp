#include "tetris.h"

void init_game(GameState& state) {
 
    //Implement your code   

    // Initialize the board with empty spaces ('.')
    state.board = std::vector<std::vector<char>>(BOARD_HEIGHT,std::vector<char> (BOARD_WIDTH,'.'));
    // Place a fixed I-block at the top center
    spawn_new_block(state);
    // Set the game to running
    state.running = true;
}

void spawn_new_block(GameState& state) {
    
    //Implement your code  
    state.block_x = 4;
    state.block_y = 0;
    // Places the I-block at (4,0)
    for(int i = 0; i < 4; i++){
        state.board[state.block_y][state.block_x+i] = '#';
    }
}