#ifndef GAME_H
#define GAME_H
#include "basis.h"

void    move(field *current, field *next);
void    reset(field prev_current, field prev_next, field *current, field *next);
void    change_fig(field **board, field *current);

#endif