#include "ui.h"
#include <ncurses/ncurses.h>

void init_ui() {
    initscr();              // Start ncurses mode
    noecho();               // Disable input echo
    cbreak();               // Disable line buffering
    keypad(stdscr, TRUE);   // Enable special keys (arrows)
    curs_set(0);            // Hide cursor
}

void draw_ui(const GameState& state) {
    //clear();

    int width = BOARD_WIDTH;
    int height = BOARD_HEIGHT;
    int offset_x = 2;
    int offset_y = 1;

    mvaddch(offset_y - 1, offset_x - 1, '+');
    mvhline(offset_y - 1, offset_x, '-', width);
    mvaddch(offset_y - 1, offset_x + width, '+');

    for (int y = 0; y < height; ++y) {
        mvaddch(offset_y + y, offset_x - 1, '|');
        for (int x = 0; x < width; ++x) {
            mvaddch(offset_y + y, offset_x + x, state.board[y][x]);
        }
        mvaddch(offset_y + y, offset_x + width, '|');
    }

    mvaddch(offset_y + height, offset_x - 1, '+');
    mvhline(offset_y + height, offset_x, '-', width);
    mvaddch(offset_y + height, offset_x + width, '+');

    refresh();
}

void cleanup_ui() {
    endwin();
}

int ui_get_input() {
    int ch = getch();
    if (ch == 'q') return 1;
    return 0;
}

