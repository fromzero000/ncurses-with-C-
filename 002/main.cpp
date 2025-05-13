#include "ui.h"
#include "tetris.h"

int main() {
    
    GameState state;
    
    init_ui();
    init_game(state);

    while (state.running) {
        draw_ui(state);
        if (ui_get_input() == 1) {
            state.running = false;
        }
    }

    cleanup_ui();
    return 0;
}