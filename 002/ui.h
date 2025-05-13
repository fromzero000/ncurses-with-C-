#ifndef UI_H
#define UI_H

#include "tetris.h"

void init_ui();
void draw_ui(const GameState& state);
void cleanup_ui();
int ui_get_input();

#endif // UI_H